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
typedef  void* term_margin ;
struct termp {int /*<<< orphan*/  (* begin ) (struct termp*) ;struct roff_meta const* argf; void* footf; void* headf; } ;
struct roff_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct termp*) ; 

void
term_begin(struct termp *p, term_margin head,
		term_margin foot, const struct roff_meta *arg)
{

	p->headf = head;
	p->footf = foot;
	p->argf = arg;
	(*p->begin)(p);
}