#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  queue_t ;
struct TYPE_7__ {TYPE_1__* b_datap; } ;
typedef  TYPE_2__ mblk_t ;
struct TYPE_6__ {scalar_t__ db_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD_RSVC ; 
 scalar_t__ QPCTL ; 
 scalar_t__ canputnext (int /*<<< orphan*/ *) ; 
 TYPE_2__* getq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  putbq (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  putnext (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int
parsersvc(
	  queue_t *q
	  )
{
	mblk_t *mp;

	while ((mp = getq(q)))
	{
		if (canputnext(q) || (mp->b_datap->db_type > QPCTL))
		{
			putnext(q, mp);
			pprintf(DD_RSVC, "parse: RSVC - putnext\n");
		}
		else
		{
			putbq(q, mp);
			pprintf(DD_RSVC, "parse: RSVC - flow control wait\n");
			break;
		}
	}
	return 0;
}