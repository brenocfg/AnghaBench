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
struct freebsd11_dirent {int dummy; } ;
struct dirent {int dummy; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int __readdir_r (int /*<<< orphan*/ *,struct dirent*,struct dirent**) ; 
 scalar_t__ freebsd11_cvtdirent (struct freebsd11_dirent*,struct dirent*) ; 

int
freebsd11_readdir_r(DIR *dirp, struct freebsd11_dirent *entry,
    struct freebsd11_dirent **result)
{
	struct dirent xentry, *xresult;
	int error;

	error = __readdir_r(dirp, &xentry, &xresult);
	if (error != 0)
		return (error);
	if (xresult != NULL) {
		if (freebsd11_cvtdirent(entry, &xentry))
			*result = entry;
		else /* should not happen due to RDU_SHORT */
			*result = NULL;
	} else
		*result = NULL;
	return (0);
}