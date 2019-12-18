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
struct evrpc_hooks_ {int /*<<< orphan*/  pause_requests; } ;
struct evrpc_hook_ctx {void (* cb ) (void*,int) ;void* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct evrpc_hook_ctx*,int /*<<< orphan*/ ) ; 
 struct evrpc_hook_ctx* mm_malloc (int) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static int
evrpc_pause_request(void *vbase, void *ctx,
    void (*cb)(void *, enum EVRPC_HOOK_RESULT))
{
	struct evrpc_hooks_ *base = vbase;
	struct evrpc_hook_ctx *pause = mm_malloc(sizeof(*pause));
	if (pause == NULL)
		return (-1);

	pause->ctx = ctx;
	pause->cb = cb;

	TAILQ_INSERT_TAIL(&base->pause_requests, pause, next);
	return (0);
}