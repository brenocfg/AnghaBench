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

/* Variables and functions */
 scalar_t__ ERANGE ; 
 scalar_t__ errno ; 
 char* getcwd (char*,size_t) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,size_t) ; 
 char* os_strdup (char const*) ; 
 size_t os_strlen (char const*) ; 

char * os_rel2abs_path(const char *rel_path)
{
	char *buf = NULL, *cwd, *ret;
	size_t len = 128, cwd_len, rel_len, ret_len;

	if (rel_path[0] == '/')
		return os_strdup(rel_path);

	for (;;) {
		buf = os_malloc(len);
		if (buf == NULL)
			return NULL;
		cwd = getcwd(buf, len);
		if (cwd == NULL) {
			os_free(buf);
			if (errno != ERANGE) {
				return NULL;
			}
			len *= 2;
		} else {
			break;
		}
	}

	cwd_len = os_strlen(cwd);
	rel_len = os_strlen(rel_path);
	ret_len = cwd_len + 1 + rel_len + 1;
	ret = os_malloc(ret_len);
	if (ret) {
		os_memcpy(ret, cwd, cwd_len);
		ret[cwd_len] = '/';
		os_memcpy(ret + cwd_len + 1, rel_path, rel_len);
		ret[ret_len - 1] = '\0';
	}
	os_free(buf);
	return ret;
}