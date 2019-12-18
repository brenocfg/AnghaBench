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
typedef  int uint8_t ;
typedef  enum pt_exec_mode { ____Placeholder_pt_exec_mode } pt_exec_mode ;
typedef  int /*<<< orphan*/  bytes ;

/* Variables and functions */
 int pte_bad_insn ; 
 int pte_internal ; 

__attribute__((used)) static inline int resolve_v(uint8_t *pbytes, enum pt_exec_mode eosz)
{
	static const uint8_t bytes[] = { 2, 4, 8 };
	unsigned int idx;

	if (!pbytes)
		return -pte_internal;

	idx = (unsigned int) eosz - 1;
	if (sizeof(bytes) <= idx)
		return -pte_bad_insn;

	*pbytes = bytes[idx];
	return 0;
}