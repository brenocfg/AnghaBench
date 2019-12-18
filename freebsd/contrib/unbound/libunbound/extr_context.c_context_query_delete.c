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
struct ctx_query {struct ctx_query* msg; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ctx_query*) ; 
 int /*<<< orphan*/  ub_resolve_free (int /*<<< orphan*/ ) ; 

void
context_query_delete(struct ctx_query* q) 
{
	if(!q) return;
	ub_resolve_free(q->res);
	free(q->msg);
	free(q);
}