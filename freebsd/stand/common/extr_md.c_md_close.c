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
struct open_file {scalar_t__ f_devdata; } ;
struct devdesc {scalar_t__ d_unit; } ;

/* Variables and functions */
 int ENXIO ; 

__attribute__((used)) static int
md_close(struct open_file *f)
{
	struct devdesc *dev;

	dev = (struct devdesc *)(f->f_devdata);
	return ((dev->d_unit != 0) ? ENXIO : 0);
}