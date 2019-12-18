#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_8__ {TYPE_2__* to_sections; TYPE_2__* to_sections_end; } ;
struct TYPE_7__ {scalar_t__ dvma; scalar_t__ dstart; scalar_t__ tvma; scalar_t__ tstart; } ;
struct TYPE_6__ {int /*<<< orphan*/  endaddr; int /*<<< orphan*/  addr; TYPE_1__* the_bfd_section; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DEPRECATED_STREQ (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * exec_bfd ; 
 TYPE_4__ exec_ops ; 
 TYPE_3__* vmap ; 

__attribute__((used)) static void
vmap_exec (void)
{
  static bfd *execbfd;
  int i;

  if (execbfd == exec_bfd)
    return;

  execbfd = exec_bfd;

  if (!vmap || !exec_ops.to_sections)
    error ("vmap_exec: vmap or exec_ops.to_sections == 0\n");

  for (i = 0; &exec_ops.to_sections[i] < exec_ops.to_sections_end; i++)
    {
      if (DEPRECATED_STREQ (".text", exec_ops.to_sections[i].the_bfd_section->name))
	{
	  exec_ops.to_sections[i].addr += vmap->tstart - vmap->tvma;
	  exec_ops.to_sections[i].endaddr += vmap->tstart - vmap->tvma;
	}
      else if (DEPRECATED_STREQ (".data", exec_ops.to_sections[i].the_bfd_section->name))
	{
	  exec_ops.to_sections[i].addr += vmap->dstart - vmap->dvma;
	  exec_ops.to_sections[i].endaddr += vmap->dstart - vmap->dvma;
	}
      else if (DEPRECATED_STREQ (".bss", exec_ops.to_sections[i].the_bfd_section->name))
	{
	  exec_ops.to_sections[i].addr += vmap->dstart - vmap->dvma;
	  exec_ops.to_sections[i].endaddr += vmap->dstart - vmap->dvma;
	}
    }
}