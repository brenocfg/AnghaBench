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
struct xfile {int dummy; } ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_FILE ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/ * kd ; 
 struct xfile* malloc (size_t) ; 
 int sysctl (int*,int,struct xfile*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
getfiles(struct xfile **abuf, size_t *alen)
{
	struct xfile *buf;
	size_t len;
	int mib[2];

	/*
	 * XXX
	 * Add emulation of KINFO_FILE here.
	 */
	if (kd != NULL)
		errx(1, "files on dead kernel, not implemented");

	mib[0] = CTL_KERN;
	mib[1] = KERN_FILE;
	if (sysctl(mib, 2, NULL, &len, NULL, 0) == -1) {
		warn("sysctl: KERN_FILE");
		return (-1);
	}
	if ((buf = malloc(len)) == NULL)
		errx(1, "malloc");
	if (sysctl(mib, 2, buf, &len, NULL, 0) == -1) {
		warn("sysctl: KERN_FILE");
		return (-1);
	}
	*abuf = buf;
	*alen = len;
	return (0);
}