#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stroptions {int so_flags; int so_hiwat; scalar_t__ so_lowat; int /*<<< orphan*/  so_readopt; } ;
typedef  int /*<<< orphan*/  queue_t ;
typedef  int /*<<< orphan*/  parsetime_t ;
struct TYPE_7__ {int b_wptr; TYPE_1__* b_datap; scalar_t__ b_rptr; } ;
typedef  TYPE_2__ mblk_t ;
struct TYPE_8__ {int /*<<< orphan*/  q_next; } ;
struct TYPE_6__ {int /*<<< orphan*/  db_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPRI_MED ; 
 int /*<<< orphan*/  DD_OPEN ; 
 int /*<<< orphan*/  MC_SERVICEDEF ; 
 int /*<<< orphan*/  MC_SERVICEIMM ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_PARSE ; 
 int /*<<< orphan*/  M_SETOPTS ; 
 int /*<<< orphan*/  RMSGD ; 
 int /*<<< orphan*/  RNORM ; 
 int SO_HIWAT ; 
 int SO_LOWAT ; 
 int SO_READOPT ; 
 TYPE_5__* WR (int /*<<< orphan*/ *) ; 
 TYPE_2__* allocb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parseprintf (int /*<<< orphan*/ ,char*) ; 
 int putctl1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putnext (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int
setup_stream(
	     queue_t *q,
	     int mode
	     )
{
	mblk_t *mp;

	mp = allocb(sizeof(struct stroptions), BPRI_MED);
	if (mp)
	{
		struct stroptions *str = (struct stroptions *)(void *)mp->b_rptr;

		str->so_flags   = SO_READOPT|SO_HIWAT|SO_LOWAT;
		str->so_readopt = (mode == M_PARSE) ? RMSGD : RNORM;
		str->so_hiwat   = (mode == M_PARSE) ? sizeof(parsetime_t) : 256;
		str->so_lowat   = 0;
		mp->b_datap->db_type = M_SETOPTS;
		mp->b_wptr += sizeof(struct stroptions);
		putnext(q, mp);
		return putctl1(WR(q)->q_next, M_CTL, (mode == M_PARSE) ? MC_SERVICEIMM :
			       MC_SERVICEDEF);
	}
	else
	{
		parseprintf(DD_OPEN,("parse: setup_stream - FAILED - no MEMORY for allocb\n"));
		return 0;
	}
}