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
typedef  int u32 ;

/* Variables and functions */
 int CMD_SHARED_DESC_HDR ; 
 int /*<<< orphan*/  PRINT_POS ; 
 int /*<<< orphan*/  init_desc (int* const,int) ; 

__attribute__((used)) static inline void init_sh_desc(u32 * const desc, u32 options)
{
	PRINT_POS;
	init_desc(desc, CMD_SHARED_DESC_HDR | options);
}