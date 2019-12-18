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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_LINE_SIZE ; 
 scalar_t__ LOAD_ELF ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  roundup2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
beri_arch_loadaddr(u_int type, void *data, uint64_t addr)
{
	uint64_t align;

	/* Align ELF objects at page boundaries; others at cache lines. */
	align = (type == LOAD_ELF) ? PAGE_SIZE : CACHE_LINE_SIZE;
	return (roundup2(addr, align));
}