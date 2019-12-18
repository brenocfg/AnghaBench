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
struct CDynamicTypeCacheMissData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CDynamicTypeCacheMissData*) ; 
 int /*<<< orphan*/  HandleDynamicTypeCacheMiss (int,struct CDynamicTypeCacheMissData*,unsigned long,unsigned long) ; 

void
__ubsan_handle_dynamic_type_cache_miss(struct CDynamicTypeCacheMissData *pData, unsigned long ulPointer, unsigned long ulHash)
{

	ASSERT(pData);

	HandleDynamicTypeCacheMiss(false, pData, ulPointer, ulHash);
}