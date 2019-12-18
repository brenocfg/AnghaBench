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
struct switch_dev {int dummy; } ;
struct ar7240sw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar7240sw_reset (struct ar7240sw*) ; 
 struct ar7240sw* sw_to_ar7240 (struct switch_dev*) ; 

__attribute__((used)) static int
ar7240_reset_switch(struct switch_dev *dev)
{
	struct ar7240sw *as = sw_to_ar7240(dev);
	ar7240sw_reset(as);
	return 0;
}