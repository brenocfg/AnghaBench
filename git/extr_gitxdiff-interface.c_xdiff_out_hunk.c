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
struct TYPE_2__ {scalar_t__ len; } ;
struct xdiff_emit_state {int /*<<< orphan*/  consume_callback_data; int /*<<< orphan*/  (* hunk_fn ) (int /*<<< orphan*/ ,long,long,long,long,char const*,long) ;TYPE_1__ remainder; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,long,long,long,long,char const*,long) ; 

__attribute__((used)) static int xdiff_out_hunk(void *priv_,
			  long old_begin, long old_nr,
			  long new_begin, long new_nr,
			  const char *func, long funclen)
{
	struct xdiff_emit_state *priv = priv_;

	if (priv->remainder.len)
		BUG("xdiff emitted hunk in the middle of a line");

	priv->hunk_fn(priv->consume_callback_data,
		      old_begin, old_nr, new_begin, new_nr,
		      func, funclen);
	return 0;
}