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
struct uio {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int dsp_io_ops (struct cdev*,struct uio*) ; 

__attribute__((used)) static int
dsp_read(struct cdev *i_dev, struct uio *buf, int flag)
{
	return (dsp_io_ops(i_dev, buf));
}