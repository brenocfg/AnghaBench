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

/* Variables and functions */
 int DNHT_SCAN_DEL ; 

__attribute__((used)) static int
do_del(void *obj, void *arg)
{
	(void)obj;
	(void)arg;
	return DNHT_SCAN_DEL;
}