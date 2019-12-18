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
struct roffreg {int val; int step; TYPE_1__ key; struct roffreg* next; } ;
struct roff {struct roffreg* regtab; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MIN ; 
 int roff_getregro (struct roff*,char const*) ; 
 int /*<<< orphan*/  roff_setregn (struct roff*,char const*,size_t,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
roff_getregn(struct roff *r, const char *name, size_t len, char sign)
{
	struct roffreg	*reg;
	int		 val;

	if ('.' == name[0] && 2 == len) {
		val = roff_getregro(r, name + 1);
		if (-1 != val)
			return val;
	}

	for (reg = r->regtab; reg; reg = reg->next) {
		if (len == reg->key.sz &&
		    0 == strncmp(name, reg->key.p, len)) {
			switch (sign) {
			case '+':
				reg->val += reg->step;
				break;
			case '-':
				reg->val -= reg->step;
				break;
			default:
				break;
			}
			return reg->val;
		}
	}

	roff_setregn(r, name, len, 0, '\0', INT_MIN);
	return 0;
}