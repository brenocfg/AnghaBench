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
struct TYPE_2__ {scalar_t__ vld; } ;

/* Variables and functions */
 TYPE_1__* HTU_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OAM_F4_SEG_HTU_ENTRY ; 
 int /*<<< orphan*/  OAM_F4_TOT_HTU_ENTRY ; 
 int /*<<< orphan*/  OAM_F5_HTU_ENTRY ; 

__attribute__((used)) static void invalidate_oam_htu_entry(void)
{
	HTU_ENTRY(OAM_F4_SEG_HTU_ENTRY)->vld = 0;
	HTU_ENTRY(OAM_F4_TOT_HTU_ENTRY)->vld = 0;
	HTU_ENTRY(OAM_F5_HTU_ENTRY)->vld = 0;
}