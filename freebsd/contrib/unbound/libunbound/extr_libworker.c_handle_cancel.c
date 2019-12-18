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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct libworker {TYPE_1__* ctx; scalar_t__ is_bg_thread; } ;
struct ctx_query {int cancelled; } ;
struct TYPE_2__ {int /*<<< orphan*/  cfglock; } ;

/* Variables and functions */
 struct ctx_query* context_deserialize_cancel (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
handle_cancel(struct libworker* w, uint8_t* buf, uint32_t len)
{
	struct ctx_query* q;
	if(w->is_bg_thread) {
		lock_basic_lock(&w->ctx->cfglock);
		q = context_deserialize_cancel(w->ctx, buf, len);
		lock_basic_unlock(&w->ctx->cfglock);
	} else {
		q = context_deserialize_cancel(w->ctx, buf, len);
	}
	if(!q) {
		/* probably simply lookup failed, i.e. the message had been
		 * processed and answered before the cancel arrived */
		return;
	}
	q->cancelled = 1;
	free(buf);
}