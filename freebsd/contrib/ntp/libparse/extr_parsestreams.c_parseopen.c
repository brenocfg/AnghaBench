#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ q_ptr; } ;
typedef  TYPE_3__ queue_t ;
struct TYPE_13__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_14__ {scalar_t__ serial; TYPE_1__ tv; } ;
struct TYPE_16__ {int /*<<< orphan*/  parse_io; TYPE_2__ parse_ppsclockev; int /*<<< orphan*/  parse_status; TYPE_3__* parse_queue; } ;
typedef  TYPE_4__ parsestream_t ;
typedef  int /*<<< orphan*/  dev_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_18__ {char* Drv_name; } ;
struct TYPE_17__ {int /*<<< orphan*/  u_error; } ;
struct TYPE_12__ {scalar_t__ q_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD_OPEN ; 
 int /*<<< orphan*/  EBUSY ; 
 int MODOPEN ; 
 int /*<<< orphan*/  M_PARSE ; 
 int OPENFAIL ; 
 int /*<<< orphan*/  PARSE_ENABLE ; 
 TYPE_10__* WR (TYPE_3__*) ; 
 int /*<<< orphan*/  bzero (scalar_t__,int) ; 
 int /*<<< orphan*/  init_linemon (TYPE_3__*) ; 
 scalar_t__ kmem_alloc (int) ; 
 int /*<<< orphan*/  kmem_free (scalar_t__,int) ; 
 int /*<<< orphan*/  parse_ioinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parsebusy ; 
 int /*<<< orphan*/  parseprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_7__ parsesync_vd ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ setup_stream (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_5__ u ; 

__attribute__((used)) static int
parseopen(
	queue_t *q,
	dev_t dev,
	int flag,
	int sflag
	)
{
	register parsestream_t *parse;
	static int notice = 0;

	parseprintf(DD_OPEN,("parse: OPEN\n"));

	if (sflag != MODOPEN)
	{			/* open only for modules */
		parseprintf(DD_OPEN,("parse: OPEN - FAILED - not MODOPEN\n"));
		return OPENFAIL;
	}

	if (q->q_ptr != (caddr_t)NULL)
	{
		u.u_error = EBUSY;
		parseprintf(DD_OPEN,("parse: OPEN - FAILED - EXCLUSIVE ONLY\n"));
		return OPENFAIL;
	}

#ifdef VDDRV
	parsebusy++;
#endif

	q->q_ptr = (caddr_t)kmem_alloc(sizeof(parsestream_t));
	if (q->q_ptr == (caddr_t)0)
	{
		parseprintf(DD_OPEN,("parse: OPEN - FAILED - no memory\n"));
#ifdef VDDRV
		parsebusy--;
#endif
		return OPENFAIL;
	}
	WR(q)->q_ptr = q->q_ptr;

	parse = (parsestream_t *)(void *)q->q_ptr;
	bzero((caddr_t)parse, sizeof(*parse));
	parse->parse_queue     = q;
	parse->parse_status    = PARSE_ENABLE;
	parse->parse_ppsclockev.tv.tv_sec  = 0;
	parse->parse_ppsclockev.tv.tv_usec = 0;
	parse->parse_ppsclockev.serial     = 0;

	if (!parse_ioinit(&parse->parse_io))
	{
		/*
		 * ok guys - beat it
		 */
		kmem_free((caddr_t)parse, sizeof(parsestream_t));
#ifdef VDDRV
		parsebusy--;
#endif
		return OPENFAIL;
	}

	if (setup_stream(q, M_PARSE))
	{
		(void) init_linemon(q);	/* hook up PPS ISR routines if possible */

		parseprintf(DD_OPEN,("parse: OPEN - SUCCEEDED\n"));

		/*
		 * I know that you know the delete key, but you didn't write this
		 * code, did you ? - So, keep the message in here.
		 */
		if (!notice)
		{
#ifdef VDDRV
			printf("%s: Copyright (C) 1991-2005, Frank Kardel\n", parsesync_vd.Drv_name);
#else
			printf("%s: Copyright (C) 1991-2005, Frank Kardel\n", "parsestreams.c,v 4.11 2005/04/16 17:32:10 kardel RELEASE_20050508_A");
#endif
			notice = 1;
		}

		return MODOPEN;
	}
	else
	{
		kmem_free((caddr_t)parse, sizeof(parsestream_t));

#ifdef VDDRV
		parsebusy--;
#endif
		return OPENFAIL;
	}
}