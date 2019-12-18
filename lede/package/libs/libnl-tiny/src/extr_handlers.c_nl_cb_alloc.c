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
struct nl_cb {int cb_refcnt; } ;
typedef  enum nl_cb_kind { ____Placeholder_nl_cb_kind } nl_cb_kind ;

/* Variables and functions */
 int NL_CB_KIND_MAX ; 
 int NL_CB_TYPE_MAX ; 
 struct nl_cb* calloc (int,int) ; 
 int /*<<< orphan*/  nl_cb_err (struct nl_cb*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_cb_set (struct nl_cb*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct nl_cb *nl_cb_alloc(enum nl_cb_kind kind)
{
	int i;
	struct nl_cb *cb;

	if (kind < 0 || kind > NL_CB_KIND_MAX)
		return NULL;

	cb = calloc(1, sizeof(*cb));
	if (!cb)
		return NULL;

	cb->cb_refcnt = 1;

	for (i = 0; i <= NL_CB_TYPE_MAX; i++)
		nl_cb_set(cb, i, kind, NULL, NULL);

	nl_cb_err(cb, kind, NULL, NULL);

	return cb;
}