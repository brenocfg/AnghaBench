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
struct brandnote_cb_arg {int /*<<< orphan*/  osrel; TYPE_1__* brandnote; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  (* trans_osrel ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  Elf_Note ;

/* Variables and functions */
 int BN_TRANSLATE_OSREL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
brandnote_cb(const Elf_Note *note, void *arg0, boolean_t *res)
{
	struct brandnote_cb_arg *arg;

	arg = arg0;

	/*
	 * Fetch the osreldate for binary from the ELF OSABI-note if
	 * necessary.
	 */
	*res = (arg->brandnote->flags & BN_TRANSLATE_OSREL) != 0 &&
	    arg->brandnote->trans_osrel != NULL ?
	    arg->brandnote->trans_osrel(note, arg->osrel) : TRUE;

	return (TRUE);
}