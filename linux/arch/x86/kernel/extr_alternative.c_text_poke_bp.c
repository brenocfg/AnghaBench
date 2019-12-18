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
struct text_poke_loc {void* detour; void* addr; size_t len; scalar_t__ opcode; } ;

/* Variables and functions */
 size_t POKE_MAX_OPCODE_SIZE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  text_poke_bp_batch (struct text_poke_loc*,int) ; 

void text_poke_bp(void *addr, const void *opcode, size_t len, void *handler)
{
	struct text_poke_loc tp = {
		.detour = handler,
		.addr = addr,
		.len = len,
	};

	if (len > POKE_MAX_OPCODE_SIZE) {
		WARN_ONCE(1, "len is larger than %d\n", POKE_MAX_OPCODE_SIZE);
		return;
	}

	memcpy((void *)tp.opcode, opcode, len);

	text_poke_bp_batch(&tp, 1);
}