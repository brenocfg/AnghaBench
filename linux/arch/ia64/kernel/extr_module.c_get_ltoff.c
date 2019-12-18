#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int next_got_entry; scalar_t__ gp; TYPE_1__* got; } ;
struct module {TYPE_2__ arch; } ;
struct got_entry {scalar_t__ val; } ;
struct TYPE_3__ {scalar_t__ sh_size; scalar_t__ sh_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static uint64_t
get_ltoff (struct module *mod, uint64_t value, int *okp)
{
	struct got_entry *got, *e;

	if (!*okp)
		return 0;

	got = (void *) mod->arch.got->sh_addr;
	for (e = got; e < got + mod->arch.next_got_entry; ++e)
		if (e->val == value)
			goto found;

	/* Not enough GOT entries? */
	BUG_ON(e >= (struct got_entry *) (mod->arch.got->sh_addr + mod->arch.got->sh_size));

	e->val = value;
	++mod->arch.next_got_entry;
  found:
	return (uint64_t) e - mod->arch.gp;
}