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
struct partial_symbol {int dummy; } ;
struct TYPE_4__ {int size; struct partial_symbol** list; struct partial_symbol** next; } ;
struct TYPE_3__ {int size; struct partial_symbol** list; struct partial_symbol** next; } ;
struct objfile {TYPE_2__ static_psymbols; int /*<<< orphan*/  md; TYPE_1__ global_psymbols; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmfree (int /*<<< orphan*/ ,struct partial_symbol**) ; 
 scalar_t__ xmmalloc (int /*<<< orphan*/ ,int) ; 

void
init_psymbol_list (struct objfile *objfile, int total_symbols)
{
  /* Free any previously allocated psymbol lists.  */

  if (objfile->global_psymbols.list)
    {
      xmfree (objfile->md, objfile->global_psymbols.list);
    }
  if (objfile->static_psymbols.list)
    {
      xmfree (objfile->md, objfile->static_psymbols.list);
    }

  /* Current best guess is that approximately a twentieth
     of the total symbols (in a debugging file) are global or static
     oriented symbols */

  objfile->global_psymbols.size = total_symbols / 10;
  objfile->static_psymbols.size = total_symbols / 10;

  if (objfile->global_psymbols.size > 0)
    {
      objfile->global_psymbols.next =
	objfile->global_psymbols.list = (struct partial_symbol **)
	xmmalloc (objfile->md, (objfile->global_psymbols.size
				* sizeof (struct partial_symbol *)));
    }
  if (objfile->static_psymbols.size > 0)
    {
      objfile->static_psymbols.next =
	objfile->static_psymbols.list = (struct partial_symbol **)
	xmmalloc (objfile->md, (objfile->static_psymbols.size
				* sizeof (struct partial_symbol *)));
    }
}