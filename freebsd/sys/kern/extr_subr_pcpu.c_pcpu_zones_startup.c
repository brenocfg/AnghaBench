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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  UMA_ZONE_PCPU ; 
 void* pcpu_zone_64 ; 
 void* pcpu_zone_int ; 
 void* uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pcpu_zones_startup(void)
{

	pcpu_zone_int = uma_zcreate("int pcpu", sizeof(int),
	    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR, UMA_ZONE_PCPU);
	pcpu_zone_64 = uma_zcreate("64 pcpu", sizeof(uint64_t),
	    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR, UMA_ZONE_PCPU);
}