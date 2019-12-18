#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** sataChannel; } ;
struct TYPE_5__ {TYPE_1__ mvSataAdapter; } ;
typedef  size_t MV_U8 ;
typedef  TYPE_2__ IAL_ADAPTER_T ;

/* Variables and functions */
 int /*<<< orphan*/  HPT_ASSERT (int) ; 
 size_t MV_SATA_CHANNELS_NUM ; 

__attribute__((used)) static void
hptmv_free_channel(IAL_ADAPTER_T *pAdapter, MV_U8 channelNum)
{
	HPT_ASSERT(channelNum < MV_SATA_CHANNELS_NUM);
	pAdapter->mvSataAdapter.sataChannel[channelNum] = NULL;
}