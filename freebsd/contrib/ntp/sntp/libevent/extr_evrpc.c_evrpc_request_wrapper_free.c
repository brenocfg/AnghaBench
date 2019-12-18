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
struct evrpc_request_wrapper {struct evrpc_request_wrapper* name; int /*<<< orphan*/ * hook_meta; } ;

/* Variables and functions */
 int /*<<< orphan*/  evrpc_hook_context_free_ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_free (struct evrpc_request_wrapper*) ; 

__attribute__((used)) static void
evrpc_request_wrapper_free(struct evrpc_request_wrapper *request)
{
	if (request->hook_meta != NULL)
		evrpc_hook_context_free_(request->hook_meta);
	mm_free(request->name);
	mm_free(request);
}