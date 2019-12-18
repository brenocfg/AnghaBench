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
struct archive_string {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_EXTRACT_SECURE_NOABSOLUTEPATHS ; 
 int ARCHIVE_EXTRACT_SECURE_NODOTDOT ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  cleanup_pathname_win (char*) ; 
 int /*<<< orphan*/  fsobj_error (int*,struct archive_string*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
cleanup_pathname_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
    int flags)
{
	char *dest, *src;
	char separator = '\0';

	dest = src = path;
	if (*src == '\0') {
		fsobj_error(a_eno, a_estr, ARCHIVE_ERRNO_MISC,
		    "Invalid empty ", "pathname");
		return (ARCHIVE_FAILED);
	}

#if defined(__CYGWIN__)
	cleanup_pathname_win(path);
#endif
	/* Skip leading '/'. */
	if (*src == '/') {
		if (flags & ARCHIVE_EXTRACT_SECURE_NOABSOLUTEPATHS) {
			fsobj_error(a_eno, a_estr, ARCHIVE_ERRNO_MISC,
			    "Path is ", "absolute");
			return (ARCHIVE_FAILED);
		}

		separator = *src++;
	}

	/* Scan the pathname one element at a time. */
	for (;;) {
		/* src points to first char after '/' */
		if (src[0] == '\0') {
			break;
		} else if (src[0] == '/') {
			/* Found '//', ignore second one. */
			src++;
			continue;
		} else if (src[0] == '.') {
			if (src[1] == '\0') {
				/* Ignore trailing '.' */
				break;
			} else if (src[1] == '/') {
				/* Skip './'. */
				src += 2;
				continue;
			} else if (src[1] == '.') {
				if (src[2] == '/' || src[2] == '\0') {
					/* Conditionally warn about '..' */
					if (flags
					    & ARCHIVE_EXTRACT_SECURE_NODOTDOT) {
						fsobj_error(a_eno, a_estr,
						    ARCHIVE_ERRNO_MISC,
						    "Path contains ", "'..'");
						return (ARCHIVE_FAILED);
					}
				}
				/*
				 * Note: Under no circumstances do we
				 * remove '..' elements.  In
				 * particular, restoring
				 * '/foo/../bar/' should create the
				 * 'foo' dir as a side-effect.
				 */
			}
		}

		/* Copy current element, including leading '/'. */
		if (separator)
			*dest++ = '/';
		while (*src != '\0' && *src != '/') {
			*dest++ = *src++;
		}

		if (*src == '\0')
			break;

		/* Skip '/' separator. */
		separator = *src++;
	}
	/*
	 * We've just copied zero or more path elements, not including the
	 * final '/'.
	 */
	if (dest == path) {
		/*
		 * Nothing got copied.  The path must have been something
		 * like '.' or '/' or './' or '/././././/./'.
		 */
		if (separator)
			*dest++ = '/';
		else
			*dest++ = '.';
	}
	/* Terminate the result. */
	*dest = '\0';
	return (ARCHIVE_OK);
}