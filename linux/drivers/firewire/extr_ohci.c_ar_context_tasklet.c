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
struct ar_context {int /*<<< orphan*/ * pointer; void* buffer; } ;

/* Variables and functions */
 unsigned int AR_BUFFERS ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  ar_context_abort (struct ar_context*,char*) ; 
 unsigned int ar_first_buffer_index (struct ar_context*) ; 
 int /*<<< orphan*/  ar_recycle_buffers (struct ar_context*,unsigned int) ; 
 unsigned int ar_search_last_active_buffer (struct ar_context*,unsigned int*) ; 
 int /*<<< orphan*/  ar_sync_buffers_for_cpu (struct ar_context*,unsigned int,unsigned int) ; 
 void* handle_ar_packets (struct ar_context*,void*,void*) ; 

__attribute__((used)) static void ar_context_tasklet(unsigned long data)
{
	struct ar_context *ctx = (struct ar_context *)data;
	unsigned int end_buffer_index, end_buffer_offset;
	void *p, *end;

	p = ctx->pointer;
	if (!p)
		return;

	end_buffer_index = ar_search_last_active_buffer(ctx,
							&end_buffer_offset);
	ar_sync_buffers_for_cpu(ctx, end_buffer_index, end_buffer_offset);
	end = ctx->buffer + end_buffer_index * PAGE_SIZE + end_buffer_offset;

	if (end_buffer_index < ar_first_buffer_index(ctx)) {
		/*
		 * The filled part of the overall buffer wraps around; handle
		 * all packets up to the buffer end here.  If the last packet
		 * wraps around, its tail will be visible after the buffer end
		 * because the buffer start pages are mapped there again.
		 */
		void *buffer_end = ctx->buffer + AR_BUFFERS * PAGE_SIZE;
		p = handle_ar_packets(ctx, p, buffer_end);
		if (p < buffer_end)
			goto error;
		/* adjust p to point back into the actual buffer */
		p -= AR_BUFFERS * PAGE_SIZE;
	}

	p = handle_ar_packets(ctx, p, end);
	if (p != end) {
		if (p > end)
			ar_context_abort(ctx, "inconsistent descriptor");
		goto error;
	}

	ctx->pointer = p;
	ar_recycle_buffers(ctx, end_buffer_index);

	return;

error:
	ctx->pointer = NULL;
}