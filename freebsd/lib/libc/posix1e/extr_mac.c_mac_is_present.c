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
 int EINVAL ; 
#define  ENOENT 129 
#define  ENOTDIR 128 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strcspn (char const*,char*) ; 
 int strlen (char const*) ; 
 int sysctlnametomib (char*,int*,size_t*) ; 

int
mac_is_present(const char *policyname)
{
	int mib[5];
	size_t siz;
	char *mibname;
	int error;

	if (policyname != NULL) {
		if (policyname[strcspn(policyname, ".=")] != '\0') {
			errno = EINVAL;
			return (-1);
		}
		mibname = malloc(sizeof("security.mac.") - 1 +
		    strlen(policyname) + sizeof(".enabled"));
		if (mibname == NULL)
			return (-1);
		strcpy(mibname, "security.mac.");
		strcat(mibname, policyname);
		strcat(mibname, ".enabled");
		siz = 5;
		error = sysctlnametomib(mibname, mib, &siz);
		free(mibname);
	} else {
		siz = 3;
		error = sysctlnametomib("security.mac", mib, &siz);
	}
	if (error == -1) {
		switch (errno) {
		case ENOTDIR:
		case ENOENT:
			return (0);
		default:
			return (error);
		}
	}
	return (1);
}