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
struct parse {int ssize; int /*<<< orphan*/ * strip; } ;
typedef  int sopno ;
typedef  int /*<<< orphan*/  sop ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 int SIZE_MAX ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
enlarge(struct parse *p, sopno size)
{
	sop *sp;

	if (p->ssize >= size)
		return;

	if ((uintptr_t)size > SIZE_MAX / sizeof(sop)) {
		SETERROR(REG_ESPACE);
		return;
	}

	sp = (sop *)realloc(p->strip, size*sizeof(sop));
	if (sp == NULL) {
		SETERROR(REG_ESPACE);
		return;
	}
	p->strip = sp;
	p->ssize = size;
}