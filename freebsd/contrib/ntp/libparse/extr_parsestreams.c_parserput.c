#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  tv; } ;
typedef  TYPE_3__ timestamp_t ;
struct TYPE_25__ {int /*<<< orphan*/  q_next; scalar_t__ q_ptr; } ;
typedef  TYPE_4__ queue_t ;
typedef  int /*<<< orphan*/  parsetime_t ;
struct TYPE_23__ {int /*<<< orphan*/  serial; int /*<<< orphan*/  tv; } ;
struct TYPE_21__ {int /*<<< orphan*/  parse_dtime; } ;
struct TYPE_26__ {int parse_status; TYPE_2__ parse_ppsclockev; TYPE_14__ parse_io; TYPE_4__* parse_queue; } ;
typedef  TYPE_5__ parsestream_t ;
struct TYPE_27__ {int b_wptr; TYPE_1__* b_datap; int /*<<< orphan*/  b_rptr; } ;
typedef  TYPE_6__ mblk_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_22__ {unsigned char db_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPRI_MED ; 
 int /*<<< orphan*/  DD_RPUT ; 
#define  M_BREAK 131 
#define  M_DATA 130 
#define  M_HANGUP 129 
#define  M_UNHANGUP 128 
 int PARSE_ENABLE ; 
 unsigned char QPCTL ; 
 scalar_t__ SYNC_ONE ; 
 scalar_t__ SYNC_ZERO ; 
 TYPE_6__* allocb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  canput (int /*<<< orphan*/ ) ; 
 int cd_invert ; 
 int /*<<< orphan*/  freemsg (TYPE_6__*) ; 
 int /*<<< orphan*/  parse_iodone (TYPE_14__*) ; 
 int /*<<< orphan*/  parse_iopps (TYPE_14__*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  parse_ioread (TYPE_14__*,unsigned int,TYPE_3__*) ; 
 int /*<<< orphan*/  parseprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  putnext (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  putq (TYPE_4__*,TYPE_6__*) ; 
 unsigned long rdchar (TYPE_6__**) ; 
 int /*<<< orphan*/  uniqtime (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
parserput(
	queue_t *q,
	mblk_t *mp
	)
{
	unsigned char type;

	switch (type = mp->b_datap->db_type)
	{
	    default:
		/*
		 * anything we don't know will be put on queue
		 * the service routine will move it to the next one
		 */
		parseprintf(DD_RPUT,("parse: parserput - forward type 0x%x\n", type));
		if (canput(q->q_next) || (mp->b_datap->db_type > QPCTL))
		{
			putnext(q, mp);
		}
		else
		    putq(q, mp);
		break;

	    case M_BREAK:
	    case M_DATA:
		    {
			    register parsestream_t * parse = (parsestream_t *)(void *)q->q_ptr;
			    register mblk_t *nmp;
			    register unsigned long ch;
			    timestamp_t ctime;

			    /*
			     * get time on packet delivery
			     */
			    uniqtime(&ctime.tv);

			    if (!(parse->parse_status & PARSE_ENABLE))
			    {
				    parseprintf(DD_RPUT,("parse: parserput - parser disabled - forward type 0x%x\n", type));
				    if (canput(q->q_next) || (mp->b_datap->db_type > QPCTL))
				    {
					    putnext(q, mp);
				    }
				    else
					putq(q, mp);
			    }
			    else
			    {
				    parseprintf(DD_RPUT,("parse: parserput - M_%s\n", (type == M_DATA) ? "DATA" : "BREAK"));

				    if (type == M_DATA)
				    {
					    /*
					     * parse packet looking for start an end characters
					     */
					    while (mp != (mblk_t *)NULL)
					    {
						    ch = rdchar(&mp);
						    if (ch != ~0 && parse_ioread(&parse->parse_io, (unsigned int)ch, &ctime))
						    {
							    /*
							     * up up and away (hopefully ...)
							     * don't press it if resources are tight or nobody wants it
							     */
							    nmp = (mblk_t *)NULL;
							    if (canput(parse->parse_queue->q_next) && (nmp = allocb(sizeof(parsetime_t), BPRI_MED)))
							    {
								    bcopy((caddr_t)&parse->parse_io.parse_dtime, (caddr_t)nmp->b_rptr, sizeof(parsetime_t));
								    nmp->b_wptr += sizeof(parsetime_t);
								    putnext(parse->parse_queue, nmp);
							    }
							    else
								if (nmp) freemsg(nmp);
							    parse_iodone(&parse->parse_io);
						    }
					    }
				    }
				    else
				    {
					    if (parse_ioread(&parse->parse_io, (unsigned int)0, &ctime))
					    {
						    /*
						     * up up and away (hopefully ...)
						     * don't press it if resources are tight or nobody wants it
						     */
						    nmp = (mblk_t *)NULL;
						    if (canput(parse->parse_queue->q_next) && (nmp = allocb(sizeof(parsetime_t), BPRI_MED)))
						    {
							    bcopy((caddr_t)&parse->parse_io.parse_dtime, (caddr_t)nmp->b_rptr, sizeof(parsetime_t));
							    nmp->b_wptr += sizeof(parsetime_t);
							    putnext(parse->parse_queue, nmp);
						    }
						    else
							if (nmp) freemsg(nmp);
						    parse_iodone(&parse->parse_io);
					    }
					    freemsg(mp);
				    }
				    break;
			    }
		    }

		    /*
		     * CD PPS support for non direct ISR hack
		     */
	    case M_HANGUP:
	    case M_UNHANGUP:
		    {
			    register parsestream_t * parse = (parsestream_t *)(void *)q->q_ptr;
			    timestamp_t ctime;
			    register mblk_t *nmp;
			    register int status = cd_invert ^ (type == M_UNHANGUP);

			    uniqtime(&ctime.tv);

			    parseprintf(DD_RPUT,("parse: parserput - M_%sHANGUP\n", (type == M_HANGUP) ? "" : "UN"));

			    if ((parse->parse_status & PARSE_ENABLE) &&
				parse_iopps(&parse->parse_io, (int)(status ? SYNC_ONE : SYNC_ZERO), &ctime))
			    {
				    nmp = (mblk_t *)NULL;
				    if (canput(parse->parse_queue->q_next) && (nmp = allocb(sizeof(parsetime_t), BPRI_MED)))
				    {
					    bcopy((caddr_t)&parse->parse_io.parse_dtime, (caddr_t)nmp->b_rptr, sizeof(parsetime_t));
					    nmp->b_wptr += sizeof(parsetime_t);
					    putnext(parse->parse_queue, nmp);
				    }
				    else
					if (nmp) freemsg(nmp);
				    parse_iodone(&parse->parse_io);
				    freemsg(mp);
			    }
			    else
				if (canput(q->q_next) || (mp->b_datap->db_type > QPCTL))
				{
					putnext(q, mp);
				}
				else
				    putq(q, mp);

			    if (status)
			    {
				    parse->parse_ppsclockev.tv = ctime.tv;
				    ++(parse->parse_ppsclockev.serial);
			    }
		    }
	}
	return 0;
}