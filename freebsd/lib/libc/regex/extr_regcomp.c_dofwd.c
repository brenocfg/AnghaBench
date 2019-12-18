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
struct parse {scalar_t__ error; int* strip; } ;
typedef  size_t sopno ;
typedef  int sop ;

/* Variables and functions */
 int OP (int) ; 
 int OPSHIFT ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
dofwd(struct parse *p, sopno pos, sop value)
{
	/* avoid making error situations worse */
	if (p->error != 0)
		return;

	assert(value < 1<<OPSHIFT);
	p->strip[pos] = OP(p->strip[pos]) | value;
}