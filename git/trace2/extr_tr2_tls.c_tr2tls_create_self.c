#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {scalar_t__ len; } ;
struct tr2tls_thread_ctx {int alloc; TYPE_1__ thread_name; scalar_t__ thread_id; int /*<<< orphan*/  nr_open_regions; int /*<<< orphan*/ * array_us_start; } ;

/* Variables and functions */
 scalar_t__ TR2_MAX_THREAD_NAME ; 
 int TR2_REGION_NESTING_INITIAL_SIZE ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,struct tr2tls_thread_ctx*) ; 
 int /*<<< orphan*/  strbuf_addf (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addstr (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_setlen (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  tr2_next_thread_id ; 
 int /*<<< orphan*/  tr2tls_key ; 
 scalar_t__ tr2tls_locked_increment (int /*<<< orphan*/ *) ; 
 struct tr2tls_thread_ctx* xcalloc (int,int) ; 

struct tr2tls_thread_ctx *tr2tls_create_self(const char *thread_name,
					     uint64_t us_thread_start)
{
	struct tr2tls_thread_ctx *ctx = xcalloc(1, sizeof(*ctx));

	/*
	 * Implicitly "tr2tls_push_self()" to capture the thread's start
	 * time in array_us_start[0].  For the main thread this gives us the
	 * application run time.
	 */
	ctx->alloc = TR2_REGION_NESTING_INITIAL_SIZE;
	ctx->array_us_start = (uint64_t *)xcalloc(ctx->alloc, sizeof(uint64_t));
	ctx->array_us_start[ctx->nr_open_regions++] = us_thread_start;

	ctx->thread_id = tr2tls_locked_increment(&tr2_next_thread_id);

	strbuf_init(&ctx->thread_name, 0);
	if (ctx->thread_id)
		strbuf_addf(&ctx->thread_name, "th%02d:", ctx->thread_id);
	strbuf_addstr(&ctx->thread_name, thread_name);
	if (ctx->thread_name.len > TR2_MAX_THREAD_NAME)
		strbuf_setlen(&ctx->thread_name, TR2_MAX_THREAD_NAME);

	pthread_setspecific(tr2tls_key, ctx);

	return ctx;
}