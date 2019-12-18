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
typedef  union key {int dummy; } key ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 int PWD_STORAGE_INITIAL ; 
 int PWD_STORAGE_MAX ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 struct passwd pwd ; 
 char* pwd_storage ; 
 int pwd_storage_size ; 

__attribute__((used)) static struct passwd *
getpw(int (*fn)(union key, struct passwd *, char *, size_t, struct passwd **),
    union key key)
{
	int		 rv;
	struct passwd	*res;

	if (pwd_storage == NULL) {
		pwd_storage = malloc(PWD_STORAGE_INITIAL);
		if (pwd_storage == NULL)
			return (NULL);
		pwd_storage_size = PWD_STORAGE_INITIAL;
	}
	do {
		rv = fn(key, &pwd, pwd_storage, pwd_storage_size, &res);
		if (res == NULL && rv == ERANGE) {
			free(pwd_storage);
			if ((pwd_storage_size << 1) > PWD_STORAGE_MAX) {
				pwd_storage = NULL;
				errno = ERANGE;
				return (NULL);
			}
			pwd_storage_size <<= 1;
			pwd_storage = malloc(pwd_storage_size);
			if (pwd_storage == NULL)
				return (NULL);
		}
	} while (res == NULL && rv == ERANGE);
	if (rv != 0)
		errno = rv;
	return (res);
}