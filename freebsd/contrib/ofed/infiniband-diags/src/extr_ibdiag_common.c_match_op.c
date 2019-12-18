#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  op_fn_t ;
struct TYPE_3__ {int /*<<< orphan*/ * fn; scalar_t__ alias; scalar_t__ name; } ;
typedef  TYPE_1__ match_rec_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 

op_fn_t *match_op(const match_rec_t match_tbl[], char *name)
{
	const match_rec_t *r;
	for (r = match_tbl; r->name; r++)
		if (!strcasecmp(r->name, name) ||
		    (r->alias && !strcasecmp(r->alias, name)))
			return r->fn;
	return NULL;
}