#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* to_lookup_symbol ) (char*,scalar_t__*) ;int /*<<< orphan*/  to_shortname; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ DEPRECATED_STREQ (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ current_target ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  stub1 (char*,scalar_t__*) ; 

void
target_link (char *modname, CORE_ADDR *t_reloc)
{
  if (DEPRECATED_STREQ (current_target.to_shortname, "rombug"))
    {
      (current_target.to_lookup_symbol) (modname, t_reloc);
      if (*t_reloc == 0)
	error ("Unable to link to %s and get relocation in rombug", modname);
    }
  else
    *t_reloc = (CORE_ADDR) -1;
}