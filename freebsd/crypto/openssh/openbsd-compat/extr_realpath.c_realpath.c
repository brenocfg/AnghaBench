#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  symlink ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  next_token ;
typedef  int /*<<< orphan*/  left ;

/* Variables and functions */
 int ELOOP ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SYMLOOP_MAX ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int readlink (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlcat (char*,char*,int) ; 
 size_t strlcpy (char*,char const*,int) ; 
 size_t strlen (char*) ; 
 char* strrchr (char*,char) ; 

char *
realpath(const char *path, char *resolved)
{
	struct stat sb;
	char *p, *q, *s;
	size_t left_len, resolved_len;
	unsigned symlinks;
	int serrno, slen, mem_allocated;
	char left[PATH_MAX], next_token[PATH_MAX], symlink[PATH_MAX];

	if (path[0] == '\0') {
		errno = ENOENT;
		return (NULL);
	}

	serrno = errno;

	if (resolved == NULL) {
		resolved = malloc(PATH_MAX);
		if (resolved == NULL)
			return (NULL);
		mem_allocated = 1;
	} else
		mem_allocated = 0;

	symlinks = 0;
	if (path[0] == '/') {
		resolved[0] = '/';
		resolved[1] = '\0';
		if (path[1] == '\0')
			return (resolved);
		resolved_len = 1;
		left_len = strlcpy(left, path + 1, sizeof(left));
	} else {
		if (getcwd(resolved, PATH_MAX) == NULL) {
			if (mem_allocated)
				free(resolved);
			else
				strlcpy(resolved, ".", PATH_MAX);
			return (NULL);
		}
		resolved_len = strlen(resolved);
		left_len = strlcpy(left, path, sizeof(left));
	}
	if (left_len >= sizeof(left) || resolved_len >= PATH_MAX) {
		errno = ENAMETOOLONG;
		goto err;
	}

	/*
	 * Iterate over path components in `left'.
	 */
	while (left_len != 0) {
		/*
		 * Extract the next path component and adjust `left'
		 * and its length.
		 */
		p = strchr(left, '/');
		s = p ? p : left + left_len;
		if (s - left >= (ptrdiff_t)sizeof(next_token)) {
			errno = ENAMETOOLONG;
			goto err;
		}
		memcpy(next_token, left, s - left);
		next_token[s - left] = '\0';
		left_len -= s - left;
		if (p != NULL)
			memmove(left, s + 1, left_len + 1);
		if (resolved[resolved_len - 1] != '/') {
			if (resolved_len + 1 >= PATH_MAX) {
				errno = ENAMETOOLONG;
				goto err;
			}
			resolved[resolved_len++] = '/';
			resolved[resolved_len] = '\0';
		}
		if (next_token[0] == '\0')
			continue;
		else if (strcmp(next_token, ".") == 0)
			continue;
		else if (strcmp(next_token, "..") == 0) {
			/*
			 * Strip the last path component except when we have
			 * single "/"
			 */
			if (resolved_len > 1) {
				resolved[resolved_len - 1] = '\0';
				q = strrchr(resolved, '/') + 1;
				*q = '\0';
				resolved_len = q - resolved;
			}
			continue;
		}

		/*
		 * Append the next path component and lstat() it. If
		 * lstat() fails we still can return successfully if
		 * there are no more path components left.
		 */
		resolved_len = strlcat(resolved, next_token, PATH_MAX);
		if (resolved_len >= PATH_MAX) {
			errno = ENAMETOOLONG;
			goto err;
		}
		if (lstat(resolved, &sb) != 0) {
			if (errno == ENOENT && p == NULL) {
				errno = serrno;
				return (resolved);
			}
			goto err;
		}
		if (S_ISLNK(sb.st_mode)) {
			if (symlinks++ > SYMLOOP_MAX) {
				errno = ELOOP;
				goto err;
			}
			slen = readlink(resolved, symlink, sizeof(symlink) - 1);
			if (slen < 0)
				goto err;
			symlink[slen] = '\0';
			if (symlink[0] == '/') {
				resolved[1] = 0;
				resolved_len = 1;
			} else if (resolved_len > 1) {
				/* Strip the last path component. */
				resolved[resolved_len - 1] = '\0';
				q = strrchr(resolved, '/') + 1;
				*q = '\0';
				resolved_len = q - resolved;
			}

			/*
			 * If there are any path components left, then
			 * append them to symlink. The result is placed
			 * in `left'.
			 */
			if (p != NULL) {
				if (symlink[slen - 1] != '/') {
					if (slen + 1 >=
					    (ptrdiff_t)sizeof(symlink)) {
						errno = ENAMETOOLONG;
						goto err;
					}
					symlink[slen] = '/';
					symlink[slen + 1] = 0;
				}
				left_len = strlcat(symlink, left, sizeof(symlink));
				if (left_len >= sizeof(symlink)) {
					errno = ENAMETOOLONG;
					goto err;
				}
			}
			left_len = strlcpy(left, symlink, sizeof(left));
		}
	}

	/*
	 * Remove trailing slash except when the resolved pathname
	 * is a single "/".
	 */
	if (resolved_len > 1 && resolved[resolved_len - 1] == '/')
		resolved[resolved_len - 1] = '\0';
	return (resolved);

err:
	if (mem_allocated)
		free(resolved);
	return (NULL);
}