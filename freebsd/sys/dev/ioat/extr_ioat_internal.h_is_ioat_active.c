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
typedef  int uint64_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int IOAT_CHANSTS_ACTIVE ; 
 int IOAT_CHANSTS_STATUS ; 

__attribute__((used)) static inline boolean_t
is_ioat_active(uint64_t status)
{
	return ((status & IOAT_CHANSTS_STATUS) == IOAT_CHANSTS_ACTIVE);
}