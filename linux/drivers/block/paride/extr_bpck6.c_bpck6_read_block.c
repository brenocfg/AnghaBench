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
typedef  int /*<<< orphan*/  PIA ;

/* Variables and functions */
 int /*<<< orphan*/  ATAPI_DATA ; 
 int /*<<< orphan*/  PPCSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppc6_rd_port16_blk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void bpck6_read_block( PIA *pi, char * buf, int len )
{
	ppc6_rd_port16_blk(PPCSTRUCT(pi),ATAPI_DATA,buf,(u32)len>>1);
}