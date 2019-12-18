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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;
struct ecore_ptt {TYPE_1__ pxp; } ;

/* Variables and functions */
 int OSAL_LE32_TO_CPU (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ecore_ptt_get_hw_addr(struct ecore_ptt *p_ptt)
{
	/* The HW is using DWORDS and we need to translate it to Bytes */
	return OSAL_LE32_TO_CPU(p_ptt->pxp.offset) << 2;
}