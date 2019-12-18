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
struct open_file {int /*<<< orphan*/ * f_fsdata; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct file*) ; 

__attribute__((used)) static int
cd9660_close(struct open_file *f)
{
	struct file *fp = (struct file *)f->f_fsdata;

	f->f_fsdata = NULL;
	free(fp);

	return 0;
}