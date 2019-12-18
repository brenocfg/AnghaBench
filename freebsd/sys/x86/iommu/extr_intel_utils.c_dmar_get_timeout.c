#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int d ; 
 TYPE_1__ dmar_hw_timeout ; 

uint64_t
dmar_get_timeout(void)
{

	return ((uint64_t)dmar_hw_timeout.tv_sec * d +
	    dmar_hw_timeout.tv_nsec);
}