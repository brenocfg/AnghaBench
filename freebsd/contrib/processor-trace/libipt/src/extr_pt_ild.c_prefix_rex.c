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
typedef  int /*<<< orphan*/  uint8_t ;
struct pt_ild {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_byte (struct pt_ild*,int /*<<< orphan*/ ) ; 
 scalar_t__ mode_64b (struct pt_ild*) ; 
 int opcode_dec (struct pt_ild*,int /*<<< orphan*/ ) ; 
 int prefix_next (struct pt_ild*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pte_internal ; 

__attribute__((used)) static int prefix_rex(struct pt_ild *ild, uint8_t length, uint8_t rex)
{
	(void) rex;

	if (!ild)
		return -pte_internal;

	if (mode_64b(ild))
		return prefix_next(ild, length, get_byte(ild, length));
	else
		return opcode_dec(ild, length);
}