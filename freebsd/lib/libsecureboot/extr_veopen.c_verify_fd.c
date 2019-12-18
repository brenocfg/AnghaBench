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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
#define  VE_FINGERPRINT_IGNORE 130 
 int VE_FINGERPRINT_NONE ; 
#define  VE_FINGERPRINT_OK 129 
#define  VE_FINGERPRINT_UNKNOWN 128 
 int VE_FINGERPRINT_WRONG ; 
 char* fingerprint_info_lookup (int,char const*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  ve_error_set (char*,char const*) ; 
 int verify_fingerprint (int,char const*,char*,int /*<<< orphan*/ ) ; 

int
verify_fd(int fd, const char *path, off_t off, struct stat *stp)
{
	struct stat st;
	char *cp;
	int rc;

	if (!stp) {
		if (fstat(fd, &st) == 0)
			stp = &st;
	}
	if (stp && !S_ISREG(stp->st_mode))
		return (0);		/* not relevant */
	cp = fingerprint_info_lookup(fd, path);
	if (!cp) {
		ve_error_set("%s: no entry", path);
		return (VE_FINGERPRINT_NONE);
	}
	rc = verify_fingerprint(fd, path, cp, off);
	switch (rc) {
	case VE_FINGERPRINT_OK:
	case VE_FINGERPRINT_IGNORE:
	case VE_FINGERPRINT_UNKNOWN:
		return (rc);
	default:
		return (VE_FINGERPRINT_WRONG);
	}
}