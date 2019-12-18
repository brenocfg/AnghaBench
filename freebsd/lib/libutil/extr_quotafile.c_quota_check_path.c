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
struct stat {scalar_t__ st_dev; } ;
struct quotafile {scalar_t__ dev; } ;

/* Variables and functions */
 int stat (char const*,struct stat*) ; 

int
quota_check_path(const struct quotafile *qf, const char *path)
{
	struct stat st;

	if (stat(path, &st) == -1)
		return (-1);
	return (st.st_dev == qf->dev);
}