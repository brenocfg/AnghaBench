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
struct roffreg {TYPE_1__ key; struct roffreg* next; } ;
struct roff {struct roffreg* regtab; } ;

/* Variables and functions */
 int roff_getregro (struct roff const*,char const*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
roff_hasregn(const struct roff *r, const char *name, size_t len)
{
	struct roffreg	*reg;
	int		 val;

	if ('.' == name[0] && 2 == len) {
		val = roff_getregro(r, name + 1);
		if (-1 != val)
			return 1;
	}

	for (reg = r->regtab; reg; reg = reg->next)
		if (len == reg->key.sz &&
		    0 == strncmp(name, reg->key.p, len))
			return 1;

	return 0;
}