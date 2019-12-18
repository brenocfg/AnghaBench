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
 int UMUTEX_NONCONSISTENT ; 
 int UMUTEX_RB_NOTRECOV ; 
 int UMUTEX_RB_OWNERDEAD ; 
 int UMUTEX_UNOWNED ; 

__attribute__((used)) static uint32_t
umtx_unlock_val(uint32_t flags, bool rb)
{

	if (rb)
		return (UMUTEX_RB_OWNERDEAD);
	else if ((flags & UMUTEX_NONCONSISTENT) != 0)
		return (UMUTEX_RB_NOTRECOV);
	else
		return (UMUTEX_UNOWNED);

}