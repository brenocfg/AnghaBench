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
struct symbol {int dummy; } ;

/* Variables and functions */
 int sym_set_tristate_value (struct symbol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yes ; 

__attribute__((used)) static inline bool sym_set_choice_value(struct symbol *ch, struct symbol *chval)
{
	return sym_set_tristate_value(chval, yes);
}