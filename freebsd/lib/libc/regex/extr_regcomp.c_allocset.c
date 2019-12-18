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
struct parse {TYPE_1__* g; } ;
typedef  int /*<<< orphan*/  cset ;
struct TYPE_2__ {scalar_t__ ncsets; int /*<<< orphan*/ * sets; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * reallocarray (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static cset *
allocset(struct parse *p)
{
	cset *cs, *ncs;

	ncs = reallocarray(p->g->sets, p->g->ncsets + 1, sizeof(*ncs));
	if (ncs == NULL) {
		SETERROR(REG_ESPACE);
		return (NULL);
	}
	p->g->sets = ncs;
	cs = &p->g->sets[p->g->ncsets++];
	memset(cs, 0, sizeof(*cs));

	return(cs);
}