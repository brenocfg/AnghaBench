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
typedef  int /*<<< orphan*/  busdma_md_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int bd_sync (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
busdma_sync_range(busdma_md_t md, int op, bus_size_t ofs, bus_size_t len)
{

	return (bd_sync(md, op, ofs, len));
}