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
struct group {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 int GRP_STORAGE_INITIAL ; 
 int GRP_STORAGE_MAX ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 struct group grp ; 
 char* grp_storage ; 
 int grp_storage_size ; 
 char* malloc (int) ; 

__attribute__((used)) static struct group *
getgr(int (*fn)(union key, struct group *, char *, size_t, struct group **),
    union key key)
{
	int		 rv;
	struct group	*res;

	if (grp_storage == NULL) {
		grp_storage = malloc(GRP_STORAGE_INITIAL);
		if (grp_storage == NULL)
			return (NULL);
		grp_storage_size = GRP_STORAGE_INITIAL;
	}
	do {
		rv = fn(key, &grp, grp_storage, grp_storage_size, &res);
		if (res == NULL && rv == ERANGE) {
			free(grp_storage);
			if ((grp_storage_size << 1) > GRP_STORAGE_MAX) {
				grp_storage = NULL;
				errno = ERANGE;
				return (NULL);
			}
			grp_storage_size <<= 1;
			grp_storage = malloc(grp_storage_size);
			if (grp_storage == NULL)
				return (NULL);
		}
	} while (res == NULL && rv == ERANGE);
	if (rv != 0)
		errno = rv;
	return (res);
}