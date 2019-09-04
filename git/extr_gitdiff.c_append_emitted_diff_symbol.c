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
struct emitted_diff_symbol {int /*<<< orphan*/  len; int /*<<< orphan*/ * line; } ;
struct diff_options {TYPE_1__* emitted_symbols; } ;
struct TYPE_2__ {scalar_t__ nr; struct emitted_diff_symbol* buf; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct emitted_diff_symbol*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct emitted_diff_symbol*,struct emitted_diff_symbol*,int) ; 
 int /*<<< orphan*/ * xmemdupz (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void append_emitted_diff_symbol(struct diff_options *o,
				       struct emitted_diff_symbol *e)
{
	struct emitted_diff_symbol *f;

	ALLOC_GROW(o->emitted_symbols->buf,
		   o->emitted_symbols->nr + 1,
		   o->emitted_symbols->alloc);
	f = &o->emitted_symbols->buf[o->emitted_symbols->nr++];

	memcpy(f, e, sizeof(struct emitted_diff_symbol));
	f->line = e->line ? xmemdupz(e->line, e->len) : NULL;
}