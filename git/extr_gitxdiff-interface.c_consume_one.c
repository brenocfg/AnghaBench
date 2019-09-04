#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xdiff_emit_state {int /*<<< orphan*/  consume_callback_data; int /*<<< orphan*/  (* line_fn ) (int /*<<< orphan*/ ,char*,unsigned long) ;} ;

/* Variables and functions */
 char* memchr (char*,char,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static void consume_one(void *priv_, char *s, unsigned long size)
{
	struct xdiff_emit_state *priv = priv_;
	char *ep;
	while (size) {
		unsigned long this_size;
		ep = memchr(s, '\n', size);
		this_size = (ep == NULL) ? size : (ep - s + 1);
		priv->line_fn(priv->consume_callback_data, s, this_size);
		size -= this_size;
		s += this_size;
	}
}