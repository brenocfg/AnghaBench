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

/* Variables and functions */
 int /*<<< orphan*/  NL_CB_DEFAULT ; 
 int /*<<< orphan*/  memcpy (struct nl_cb*,struct nl_cb*,int) ; 
 struct nl_cb* nl_cb_alloc (int /*<<< orphan*/ ) ; 

struct nl_cb *nl_cb_clone(struct nl_cb *orig)
{
	struct nl_cb *cb;
	
	cb = nl_cb_alloc(NL_CB_DEFAULT);
	if (!cb)
		return NULL;

	memcpy(cb, orig, sizeof(*orig));
	cb->cb_refcnt = 1;

	return cb;
}