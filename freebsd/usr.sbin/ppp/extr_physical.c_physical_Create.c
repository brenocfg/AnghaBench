#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int gather; int /*<<< orphan*/ * parent; int /*<<< orphan*/  total; } ;
struct TYPE_15__ {int len; int /*<<< orphan*/  ccp; int /*<<< orphan*/  lcp; int /*<<< orphan*/  proto_out; int /*<<< orphan*/  proto_in; int /*<<< orphan*/  Queue; TYPE_5__ stats; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct TYPE_24__ {scalar_t__ delay; int /*<<< orphan*/  necessity; } ;
struct TYPE_25__ {TYPE_8__ cd; int /*<<< orphan*/  ndev; int /*<<< orphan*/  devlist; int /*<<< orphan*/  parity; int /*<<< orphan*/  speed; int /*<<< orphan*/  rts_cts; } ;
struct TYPE_23__ {char* full; char* base; } ;
struct TYPE_22__ {scalar_t__ sz; } ;
struct physical {int type; int fd; TYPE_10__ link; TYPE_9__ cfg; scalar_t__ session_owner; scalar_t__ Utmp; TYPE_7__ name; TYPE_6__ input; struct datalink* dl; scalar_t__ connect_count; int /*<<< orphan*/ * out; int /*<<< orphan*/  async; int /*<<< orphan*/  hdlc; int /*<<< orphan*/ * handler; } ;
struct datalink {int /*<<< orphan*/  fsmp; TYPE_11__* bundle; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_17__ {int /*<<< orphan*/  total; } ;
struct TYPE_18__ {TYPE_1__ stats; } ;
struct TYPE_19__ {TYPE_2__ link; scalar_t__ active; } ;
struct TYPE_20__ {TYPE_3__ mp; } ;
struct TYPE_16__ {TYPE_4__ ncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD_DEFAULT ; 
 int /*<<< orphan*/  CS8 ; 
 int /*<<< orphan*/  MODEM_CTSRTS ; 
 int /*<<< orphan*/  MODEM_LIST ; 
 int /*<<< orphan*/  MODEM_SPEED ; 
 int /*<<< orphan*/  NMODEMS ; 
 int /*<<< orphan*/  PHYSICAL_LINK ; 
 int /*<<< orphan*/  SAMPLE_PERIOD ; 
 int /*<<< orphan*/  async_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccp_Init (int /*<<< orphan*/ *,TYPE_11__*,TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdlc_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcp_Init (int /*<<< orphan*/ *,TYPE_11__*,TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_EmptyStack (TYPE_10__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  physical_SetDescriptor (struct physical*) ; 
 int /*<<< orphan*/  throughput_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct physical *
physical_Create(struct datalink *dl, int type)
{
  struct physical *p;

  p = (struct physical *)malloc(sizeof(struct physical));
  if (!p)
    return NULL;

  p->link.type = PHYSICAL_LINK;
  p->link.name = dl->name;
  p->link.len = sizeof *p;

  /* The sample period is fixed - see physical2iov() & iov2physical() */
  throughput_init(&p->link.stats.total, SAMPLE_PERIOD);
  p->link.stats.parent = dl->bundle->ncp.mp.active ?
    &dl->bundle->ncp.mp.link.stats.total : NULL;
  p->link.stats.gather = 1;

  memset(p->link.Queue, '\0', sizeof p->link.Queue);
  memset(p->link.proto_in, '\0', sizeof p->link.proto_in);
  memset(p->link.proto_out, '\0', sizeof p->link.proto_out);
  link_EmptyStack(&p->link);

  p->handler = NULL;
  physical_SetDescriptor(p);
  p->type = type;

  hdlc_Init(&p->hdlc, &p->link.lcp);
  async_Init(&p->async);

  p->fd = -1;
  p->out = NULL;
  p->connect_count = 0;
  p->dl = dl;
  p->input.sz = 0;
  *p->name.full = '\0';
  p->name.base = p->name.full;

  p->Utmp = 0;
  p->session_owner = (pid_t)-1;

  p->cfg.rts_cts = MODEM_CTSRTS;
  p->cfg.speed = MODEM_SPEED;
  p->cfg.parity = CS8;
  memcpy(p->cfg.devlist, MODEM_LIST, sizeof MODEM_LIST);
  p->cfg.ndev = NMODEMS;
  p->cfg.cd.necessity = CD_DEFAULT;
  p->cfg.cd.delay = 0;		/* reconfigured or device specific default */

  lcp_Init(&p->link.lcp, dl->bundle, &p->link, &dl->fsmp);
  ccp_Init(&p->link.ccp, dl->bundle, &p->link, &dl->fsmp);

  return p;
}