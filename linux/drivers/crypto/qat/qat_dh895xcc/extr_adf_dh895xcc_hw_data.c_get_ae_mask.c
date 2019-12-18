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
typedef  int uint32_t ;

/* Variables and functions */
 int ADF_DH895XCC_ACCELENGINES_MASK ; 

__attribute__((used)) static uint32_t get_ae_mask(uint32_t fuse)
{
	return (~fuse) & ADF_DH895XCC_ACCELENGINES_MASK;
}