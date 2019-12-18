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
struct TYPE_4__ {char const* name; scalar_t__ wc; } ;
typedef  TYPE_1__ charmap_t ;

/* Variables and functions */
 TYPE_1__* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cmap_sym ; 

int
lookup_charmap(const char *sym, wchar_t *wc)
{
	charmap_t	srch;
	charmap_t	*n;

	srch.name = sym;
	n = RB_FIND(cmap_sym, &cmap_sym, &srch);
	if (n && n->wc != (wchar_t)-1) {
		if (wc)
			*wc = n->wc;
		return (0);
	}
	return (-1);
}