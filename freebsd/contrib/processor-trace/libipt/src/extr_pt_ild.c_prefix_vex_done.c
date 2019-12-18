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
typedef  scalar_t__ uint8_t ;
struct pt_ild {int /*<<< orphan*/  nominal_opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_byte (struct pt_ild*,scalar_t__) ; 
 int modrm_dec (struct pt_ild*,scalar_t__) ; 
 int pte_internal ; 

__attribute__((used)) static inline int prefix_vex_done(struct pt_ild *ild, uint8_t length)
{
	if (!ild)
		return -pte_internal;

	ild->nominal_opcode = get_byte(ild, length);

	return modrm_dec(ild, length + 1);
}