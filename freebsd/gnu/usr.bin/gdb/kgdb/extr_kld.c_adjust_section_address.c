#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct section_table {scalar_t__ endaddr; scalar_t__ addr; TYPE_1__* bfd; struct bfd_section* the_bfd_section; } ;
struct bfd_section {int dummy; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ bfd ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int DYNAMIC ; 
 int EXEC_P ; 
 scalar_t__ align_power (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_section_alignment (TYPE_1__*,struct bfd_section*) ; 
 scalar_t__ bfd_section_size (TYPE_1__*,struct bfd_section*) ; 

__attribute__((used)) static void
adjust_section_address (struct section_table *sec, CORE_ADDR *curr_base)
{
	struct bfd_section *asect = sec->the_bfd_section;
	bfd *abfd = sec->bfd;

	if ((abfd->flags & (EXEC_P | DYNAMIC)) != 0) {
		sec->addr += *curr_base;
		sec->endaddr += *curr_base;
		return;
	}

	*curr_base = align_power(*curr_base,
	    bfd_get_section_alignment(abfd, asect));
	sec->addr = *curr_base;
	sec->endaddr = sec->addr + bfd_section_size(abfd, asect);
	*curr_base = sec->endaddr;
}