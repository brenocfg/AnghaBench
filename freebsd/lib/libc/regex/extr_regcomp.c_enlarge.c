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
struct parse {scalar_t__ ssize; int /*<<< orphan*/ * strip; } ;
typedef  scalar_t__ sopno ;
typedef  int /*<<< orphan*/  sop ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reallocarray (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int
enlarge(struct parse *p, sopno size)
{
	sop *sp;

	if (p->ssize >= size)
		return 1;

	sp = reallocarray(p->strip, size, sizeof(sop));
	if (sp == NULL) {
		SETERROR(REG_ESPACE);
		return 0;
	}
	p->strip = sp;
	p->ssize = size;
	return 1;
}