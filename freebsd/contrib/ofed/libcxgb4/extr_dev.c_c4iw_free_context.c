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
struct ibv_context {int dummy; } ;
struct c4iw_context {scalar_t__ status_page_size; int /*<<< orphan*/  status_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct c4iw_context*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,scalar_t__) ; 
 struct c4iw_context* to_c4iw_context (struct ibv_context*) ; 

__attribute__((used)) static void c4iw_free_context(struct ibv_context *ibctx)
{
	struct c4iw_context *context = to_c4iw_context(ibctx);

	if (context->status_page_size)
		munmap(context->status_page, context->status_page_size);
	free(context);
}