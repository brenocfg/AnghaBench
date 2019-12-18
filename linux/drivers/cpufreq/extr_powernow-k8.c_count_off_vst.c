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
struct powernow_k8_data {int vstable; } ;

/* Variables and functions */
 int VST_UNITS_20US ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void count_off_vst(struct powernow_k8_data *data)
{
	udelay(data->vstable * VST_UNITS_20US);
}