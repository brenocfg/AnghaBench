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
struct open_file {struct devdesc* f_devdata; } ;
struct devdesc {int /*<<< orphan*/  d_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  host_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hostdisk_close(struct open_file *f)
{
	struct devdesc *desc = f->f_devdata;

	host_close(desc->d_unit);
	return (0);
}