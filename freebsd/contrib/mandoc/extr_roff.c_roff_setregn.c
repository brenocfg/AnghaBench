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
struct TYPE_2__ {size_t sz; int /*<<< orphan*/  p; } ;
struct roffreg {int val; int step; struct roffreg* next; TYPE_1__ key; } ;
struct roff {struct roffreg* regtab; } ;

/* Variables and functions */
 int INT_MIN ; 
 struct roffreg* mandoc_malloc (int) ; 
 int /*<<< orphan*/  mandoc_strndup (char const*,size_t) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static void
roff_setregn(struct roff *r, const char *name, size_t len,
    int val, char sign, int step)
{
	struct roffreg	*reg;

	/* Search for an existing register with the same name. */
	reg = r->regtab;

	while (reg != NULL && (reg->key.sz != len ||
	    strncmp(reg->key.p, name, len) != 0))
		reg = reg->next;

	if (NULL == reg) {
		/* Create a new register. */
		reg = mandoc_malloc(sizeof(struct roffreg));
		reg->key.p = mandoc_strndup(name, len);
		reg->key.sz = len;
		reg->val = 0;
		reg->step = 0;
		reg->next = r->regtab;
		r->regtab = reg;
	}

	if ('+' == sign)
		reg->val += val;
	else if ('-' == sign)
		reg->val -= val;
	else
		reg->val = val;
	if (step != INT_MIN)
		reg->step = step;
}