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
struct nx842_devdata {scalar_t__ max_sg_len; scalar_t__ max_sync_sg; scalar_t__ max_sync_size; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int nx842_OF_set_defaults(struct nx842_devdata *devdata)
{
	if (devdata) {
		devdata->max_sync_size = 0;
		devdata->max_sync_sg = 0;
		devdata->max_sg_len = 0;
		return 0;
	} else
		return -ENOENT;
}