#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* q_ptr; } ;
typedef  TYPE_1__ queue_t ;
struct TYPE_10__ {int /*<<< orphan*/  parse_io; TYPE_1__* parse_dqueue; } ;
typedef  TYPE_2__ parsestream_t ;
typedef  void* caddr_t ;
struct TYPE_11__ {void* q_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD_CLOSE ; 
 TYPE_7__* WR (TYPE_1__*) ; 
 int /*<<< orphan*/  close_linemon (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (void*,int) ; 
 int /*<<< orphan*/  parse_ioend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qprocsoff (TYPE_1__*) ; 
 unsigned long splhigh () ; 
 int /*<<< orphan*/  splx (unsigned long) ; 

__attribute__((used)) static int
parseclose(
	   queue_t *q,
	   int flags
	   )
{
	register parsestream_t *parse = (parsestream_t *)q->q_ptr;
	register unsigned long s;

	pprintf(DD_CLOSE, "parse: CLOSE\n");

	qprocsoff(q);

	s = splhigh();

	if (parse->parse_dqueue)
	    close_linemon(parse->parse_dqueue, q);
	parse->parse_dqueue = (queue_t *)0;

	(void) splx(s);

	parse_ioend(&parse->parse_io);

	kmem_free((caddr_t)parse, sizeof(parsestream_t));

	q->q_ptr = (caddr_t)NULL;
	WR(q)->q_ptr = (caddr_t)NULL;

	return 0;
}