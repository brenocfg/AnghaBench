#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_16__ ;

/* Type definitions */
struct TYPE_27__ {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_29__ {TYPE_2__ tv; } ;
typedef  TYPE_4__ timestamp_t ;
struct TYPE_30__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  TYPE_5__ timespec_t ;
struct TYPE_31__ {scalar_t__ q_ptr; } ;
typedef  TYPE_6__ queue_t ;
typedef  int /*<<< orphan*/  parsetime_t ;
struct TYPE_28__ {int /*<<< orphan*/  serial; TYPE_2__ tv; } ;
struct TYPE_25__ {int /*<<< orphan*/  parse_dtime; } ;
struct TYPE_32__ {int parse_status; TYPE_3__ parse_ppsclockev; TYPE_16__ parse_io; TYPE_6__* parse_queue; } ;
typedef  TYPE_7__ parsestream_t ;
struct TYPE_33__ {int b_wptr; TYPE_1__* b_datap; int /*<<< orphan*/  b_rptr; } ;
typedef  TYPE_8__ mblk_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_26__ {unsigned char db_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPRI_MED ; 
 int /*<<< orphan*/  DD_RPUT ; 
#define  M_BREAK 131 
#define  M_DATA 130 
#define  M_HANGUP 129 
#define  M_UNHANGUP 128 
 int PARSE_ENABLE ; 
 unsigned char QPCTL ; 
 int /*<<< orphan*/  SYNC_ONE ; 
 int /*<<< orphan*/  SYNC_ZERO ; 
 TYPE_8__* allocb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  canputnext (TYPE_6__*) ; 
 int cd_invert ; 
 int /*<<< orphan*/  freemsg (TYPE_8__*) ; 
 int /*<<< orphan*/  gethrestime (TYPE_5__*) ; 
 int /*<<< orphan*/  parse_iodone (TYPE_16__*) ; 
 int /*<<< orphan*/  parse_iopps (TYPE_16__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  parse_ioread (TYPE_16__*,unsigned int,TYPE_4__*) ; 
 int /*<<< orphan*/  pprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  putnext (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  putq (TYPE_6__*,TYPE_8__*) ; 
 unsigned long rdchar (TYPE_8__**) ; 

__attribute__((used)) static int
parserput(
	  queue_t *q,
	  mblk_t *imp
	  )
{
	register unsigned char type;
	mblk_t *mp = imp;

	switch (type = mp->b_datap->db_type)
	{
	    default:
		/*
		 * anything we don't know will be put on queue
		 * the service routine will move it to the next one
		 */
		pprintf(DD_RPUT, "parse: parserput - forward type 0x%x\n", type);

		if (canputnext(q) || (mp->b_datap->db_type > QPCTL))
		{
			putnext(q, mp);
		}
		else
		    putq(q, mp);
		break;

	    case M_BREAK:
	    case M_DATA:
		    {
			    register parsestream_t * parse = (parsestream_t *)q->q_ptr;
			    register mblk_t *nmp;
			    register unsigned long ch;
			    timestamp_t c_time;
			    timespec_t hres_time;

			    /*
			     * get time on packet delivery
			     */
			    gethrestime(&hres_time);
			    c_time.tv.tv_sec  = hres_time.tv_sec;
			    c_time.tv.tv_usec = hres_time.tv_nsec / 1000;

			    if (!(parse->parse_status & PARSE_ENABLE))
			    {
				    pprintf(DD_RPUT, "parse: parserput - parser disabled - forward type 0x%x\n", type);
				    if (canputnext(q) || (mp->b_datap->db_type > QPCTL))
				    {
					    putnext(q, mp);
				    }
				    else
					putq(q, mp);
			    }
			    else
			    {
				    pprintf(DD_RPUT, "parse: parserput - M_%s\n", (type == M_DATA) ? "DATA" : "BREAK");
				    if (type == M_DATA)
				    {
					    /*
					     * parse packet looking for start an end characters
					     */
					    while (mp != (mblk_t *)NULL)
					    {
						    ch = rdchar(&mp);
						    if (ch != ~0 && parse_ioread(&parse->parse_io, (unsigned int)ch, &c_time))
						    {
							    /*
							     * up up and away (hopefully ...)
							     * don't press it if resources are tight or nobody wants it
							     */
							    nmp = (mblk_t *)NULL;
							    if (canputnext(parse->parse_queue) && (nmp = allocb(sizeof(parsetime_t), BPRI_MED)))
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
					    if (parse_ioread(&parse->parse_io, (unsigned int)0, &c_time))
					    {
						    /*
						     * up up and away (hopefully ...)
						     * don't press it if resources are tight or nobody wants it
						     */
						    nmp = (mblk_t *)NULL;
						    if (canputnext(parse->parse_queue) && (nmp = allocb(sizeof(parsetime_t), BPRI_MED)))
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
			    register parsestream_t * parse = (parsestream_t *)q->q_ptr;
			    timestamp_t c_time;
			    timespec_t hres_time;
			    register mblk_t *nmp;
			    register int status = cd_invert ^ (type == M_UNHANGUP);

			    gethrestime(&hres_time);
			    c_time.tv.tv_sec  = hres_time.tv_sec;
			    c_time.tv.tv_usec = hres_time.tv_nsec / 1000;

			    pprintf(DD_RPUT, "parse: parserput - M_%sHANGUP\n", (type == M_HANGUP) ? "" : "UN");

			    if ((parse->parse_status & PARSE_ENABLE) &&
				parse_iopps(&parse->parse_io, status ? SYNC_ONE : SYNC_ZERO, &c_time))
			    {
				    nmp = (mblk_t *)NULL;
				    if (canputnext(parse->parse_queue) && (nmp = allocb(sizeof(parsetime_t), BPRI_MED)))
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
				if (canputnext(q) || (mp->b_datap->db_type > QPCTL))
				{
					putnext(q, mp);
				}
				else
				    putq(q, mp);

			    if (status)
			    {
				    parse->parse_ppsclockev.tv = c_time.tv;
				    ++(parse->parse_ppsclockev.serial);
			    }
		    }
	}
	return 0;
}