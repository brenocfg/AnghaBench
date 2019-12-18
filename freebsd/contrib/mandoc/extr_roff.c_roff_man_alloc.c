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
struct roff_man {char const* os_s; int quick; struct roff* roff; } ;
struct roff {struct roff_man* man; } ;

/* Variables and functions */
 struct roff_man* mandoc_calloc (int,int) ; 
 int /*<<< orphan*/  roff_man_alloc1 (struct roff_man*) ; 

struct roff_man *
roff_man_alloc(struct roff *roff, const char *os_s, int quick)
{
	struct roff_man *man;

	man = mandoc_calloc(1, sizeof(*man));
	man->roff = roff;
	man->os_s = os_s;
	man->quick = quick;
	roff_man_alloc1(man);
	roff->man = man;
	return man;
}