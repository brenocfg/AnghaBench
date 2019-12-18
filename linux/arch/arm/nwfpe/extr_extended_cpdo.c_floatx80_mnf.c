#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct roundingData {int dummy; } ;
struct TYPE_4__ {int high; } ;
typedef  TYPE_1__ floatx80 ;

/* Variables and functions */

__attribute__((used)) static floatx80 floatx80_mnf(struct roundingData *roundData, floatx80 rFm)
{
	rFm.high ^= 0x8000;
	return rFm;
}