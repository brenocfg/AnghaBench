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
typedef  scalar_t__ wchar_t ;
struct TYPE_4__ {char* name; scalar_t__ wc; } ;
typedef  TYPE_1__ charmap_t ;

/* Variables and functions */
 TYPE_1__* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  add_charmap_impl (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmap_sym ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ undefok ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

void
add_charmap_undefined(char *sym)
{
	charmap_t srch;
	charmap_t *cm = NULL;

	srch.name = sym;
	cm = RB_FIND(cmap_sym, &cmap_sym, &srch);

	if ((undefok == 0) && ((cm == NULL) || (cm->wc == (wchar_t)-1))) {
		warn("undefined symbol <%s>", sym);
		add_charmap_impl(sym, -1, 0);
	} else {
		free(sym);
	}
}