#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_21__ ;
typedef  struct TYPE_33__   TYPE_20__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_19__ ;
typedef  struct TYPE_30__   TYPE_18__ ;
typedef  struct TYPE_29__   TYPE_17__ ;
typedef  struct TYPE_28__   TYPE_16__ ;
typedef  struct TYPE_27__   TYPE_15__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {char* name; int logok; TYPE_14__* rule; } ;
struct TYPE_25__ {char* name; int logok; TYPE_12__* rule; } ;
struct TYPE_23__ {int fragok; int logok; char* name; TYPE_10__* rule; } ;
struct TYPE_42__ {int fragok; int logok; char* name; TYPE_8__* rule; } ;
struct TYPE_34__ {TYPE_15__ alive; TYPE_13__ dial; TYPE_11__ out; TYPE_9__ in; } ;
struct TYPE_30__ {TYPE_21__ timer; } ;
struct TYPE_29__ {int fd; } ;
struct TYPE_28__ {scalar_t__ done; TYPE_21__ timer; } ;
struct TYPE_40__ {int /*<<< orphan*/  Write; int /*<<< orphan*/  Read; int /*<<< orphan*/  IsSet; int /*<<< orphan*/  UpdateSet; int /*<<< orphan*/  type; } ;
struct TYPE_31__ {char* Name; scalar_t__ fd; int header; } ;
struct TYPE_39__ {int all; scalar_t__ open; } ;
struct TYPE_37__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_36__ {char* name; char* key; } ;
struct TYPE_35__ {scalar_t__ min_timeout; int /*<<< orphan*/  timeout; } ;
struct TYPE_38__ {unsigned long long optmask; char* label; TYPE_4__ choked; int /*<<< orphan*/  ifqueue; TYPE_3__ auth; TYPE_2__ idle; } ;
struct TYPE_32__ {struct bundle* object; int /*<<< orphan*/  LayerFinish; int /*<<< orphan*/  LayerDown; int /*<<< orphan*/  LayerUp; int /*<<< orphan*/  LayerStart; } ;
struct bundle {int unit; int /*<<< orphan*/  ncp; int /*<<< orphan*/ * iface; int /*<<< orphan*/  radius; TYPE_18__ choked; TYPE_17__ notify; TYPE_16__ idle; TYPE_21__ filter; TYPE_7__ desc; TYPE_19__ dev; int /*<<< orphan*/ * links; scalar_t__ upat; TYPE_6__ phys_type; TYPE_5__ cfg; TYPE_1__ fsm; scalar_t__ NatEnabled; scalar_t__ CleaningUp; int /*<<< orphan*/  phase; scalar_t__ routing_seq; scalar_t__ bandwidth; } ;
struct TYPE_41__ {void* f_action; } ;
struct TYPE_33__ {scalar_t__ ipv6_available; } ;
struct TYPE_26__ {void* f_action; } ;
struct TYPE_24__ {void* f_action; } ;
struct TYPE_22__ {void* f_action; } ;

/* Variables and functions */
 void* A_NONE ; 
 int /*<<< orphan*/  BUNDLE_DESCRIPTOR ; 
 int /*<<< orphan*/  CHOKED_TIMEOUT ; 
 int /*<<< orphan*/  DEF_IFQUEUE ; 
 int ENOENT ; 
 int ENXIO ; 
 scalar_t__ ID0ioctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ID0open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFACE_CLEAR_ALL ; 
 int IFF_MULTICAST ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  LOAD_VERBOSLY ; 
 int /*<<< orphan*/  LogALERT ; 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  LogWARN ; 
 int MAXFILTERS ; 
 int /*<<< orphan*/  NCP_IDLE_TIMEOUT ; 
 unsigned long long OPT_IDCHECK ; 
 int /*<<< orphan*/  OPT_IPCP ; 
 int /*<<< orphan*/  OPT_IPV6CP ; 
 unsigned long long OPT_LOOPBACK ; 
 unsigned long long OPT_NAS_IDENTIFIER ; 
 unsigned long long OPT_NAS_IP_ADDRESS ; 
 unsigned long long OPT_SROUTES ; 
 unsigned long long OPT_TCPMSSFIXUP ; 
 unsigned long long OPT_THROUGHPUT ; 
 unsigned long long OPT_UTMP ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PHASE_DEAD ; 
 int /*<<< orphan*/  TUNSIFHEAD ; 
 int /*<<< orphan*/  TUNSIFMODE ; 
 int /*<<< orphan*/  TUNSLMODE ; 
 int /*<<< orphan*/  bundle_DescriptorRead ; 
 int /*<<< orphan*/  bundle_DescriptorWrite ; 
 int /*<<< orphan*/  bundle_IsSet ; 
 int /*<<< orphan*/  bundle_LayerDown ; 
 int /*<<< orphan*/  bundle_LayerFinish ; 
 int /*<<< orphan*/  bundle_LayerStart ; 
 int /*<<< orphan*/  bundle_LayerUp ; 
 int /*<<< orphan*/  bundle_LockTun (struct bundle*) ; 
 int /*<<< orphan*/  bundle_UpdateSet ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/ * datalink_Create (char*,struct bundle*,int) ; 
 int errno ; 
 int /*<<< orphan*/  iface_Clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iface_Create (char const*) ; 
 int /*<<< orphan*/  iface_Free (int /*<<< orphan*/ *) ; 
 scalar_t__ loadmodules (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  log_SetTun (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_21__*,char,int) ; 
 int /*<<< orphan*/  ncp_Init (int /*<<< orphan*/ *,struct bundle*) ; 
 int /*<<< orphan*/  opt_enable (struct bundle*,int /*<<< orphan*/ ) ; 
 TYPE_20__ probe ; 
 int /*<<< orphan*/  radius_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 
 char const* strerror (int) ; 
 char* strrchr (char*,char) ; 

struct bundle *
bundle_Create(const char *prefix, int type, int unit)
{
  static struct bundle bundle;		/* there can be only one */
  int enoentcount, err, minunit, maxunit;
  const char *ifname;
#if defined(__FreeBSD__) && !defined(NOKLDLOAD)
  int kldtried;
#endif
#if defined(TUNSIFMODE) || defined(TUNSLMODE) || defined(TUNSIFHEAD)
  int iff;
#endif

  if (bundle.iface != NULL) {	/* Already allocated ! */
    log_Printf(LogALERT, "bundle_Create:  There's only one BUNDLE !\n");
    return NULL;
  }

  if (unit == -1) {
    minunit = 0;
    maxunit = -1;
  } else {
    minunit = unit;
    maxunit = unit + 1;
  }
  err = ENOENT;
  enoentcount = 0;
#if defined(__FreeBSD__) && !defined(NOKLDLOAD)
  kldtried = 0;
#endif
  for (bundle.unit = minunit; bundle.unit != maxunit; bundle.unit++) {
    snprintf(bundle.dev.Name, sizeof bundle.dev.Name, "%s%d",
             prefix, bundle.unit);
    bundle.dev.fd = ID0open(bundle.dev.Name, O_RDWR);
    if (bundle.dev.fd >= 0)
      break;
    else if (errno == ENXIO || errno == ENOENT) {
#if defined(__FreeBSD__) && !defined(NOKLDLOAD)
      if (bundle.unit == minunit && !kldtried++) {
        /*
         * Attempt to load the tunnel interface KLD if it isn't loaded
         * already.
         */
        if (loadmodules(LOAD_VERBOSLY, "if_tun", NULL))
          bundle.unit--;
        continue;
      }
#endif
      if (errno != ENOENT || ++enoentcount > 2) {
        err = errno;
	break;
      }
    } else
      err = errno;
  }

  if (bundle.dev.fd < 0) {
    if (unit == -1)
      log_Printf(LogWARN, "No available tunnel devices found (%s)\n",
                strerror(err));
    else
      log_Printf(LogWARN, "%s%d: %s\n", prefix, unit, strerror(err));
    return NULL;
  }

  log_SetTun(bundle.unit, NULL);

  ifname = strrchr(bundle.dev.Name, '/');
  if (ifname == NULL)
    ifname = bundle.dev.Name;
  else
    ifname++;

  bundle.iface = iface_Create(ifname);
  if (bundle.iface == NULL) {
    close(bundle.dev.fd);
    return NULL;
  }

#ifdef TUNSIFMODE
  /* Make sure we're POINTOPOINT & IFF_MULTICAST */
  iff = IFF_POINTOPOINT | IFF_MULTICAST;
  if (ID0ioctl(bundle.dev.fd, TUNSIFMODE, &iff) < 0)
    log_Printf(LogERROR, "bundle_Create: ioctl(TUNSIFMODE): %s\n",
	       strerror(errno));
#endif

#ifdef TUNSLMODE
  /* Make sure we're not prepending sockaddrs */
  iff = 0;
  if (ID0ioctl(bundle.dev.fd, TUNSLMODE, &iff) < 0)
    log_Printf(LogERROR, "bundle_Create: ioctl(TUNSLMODE): %s\n",
	       strerror(errno));
#endif

#ifdef TUNSIFHEAD
  /* We want the address family please ! */
  iff = 1;
  if (ID0ioctl(bundle.dev.fd, TUNSIFHEAD, &iff) < 0) {
    log_Printf(LogERROR, "bundle_Create: ioctl(TUNSIFHEAD): %s\n",
	       strerror(errno));
    bundle.dev.header = 0;
  } else
    bundle.dev.header = 1;
#else
#ifdef __OpenBSD__
  /* Always present for OpenBSD */
  bundle.dev.header = 1;
#else
  /*
   * If TUNSIFHEAD isn't available and we're not OpenBSD, assume
   * everything's AF_INET (hopefully the tun device won't pass us
   * anything else !).
   */
  bundle.dev.header = 0;
#endif
#endif

  log_Printf(LogPHASE, "Using interface: %s\n", ifname);

  bundle.bandwidth = 0;
  bundle.routing_seq = 0;
  bundle.phase = PHASE_DEAD;
  bundle.CleaningUp = 0;
  bundle.NatEnabled = 0;

  bundle.fsm.LayerStart = bundle_LayerStart;
  bundle.fsm.LayerUp = bundle_LayerUp;
  bundle.fsm.LayerDown = bundle_LayerDown;
  bundle.fsm.LayerFinish = bundle_LayerFinish;
  bundle.fsm.object = &bundle;

  bundle.cfg.idle.timeout = NCP_IDLE_TIMEOUT;
  bundle.cfg.idle.min_timeout = 0;
  *bundle.cfg.auth.name = '\0';
  *bundle.cfg.auth.key = '\0';
  bundle.cfg.optmask = (1ull << OPT_IDCHECK) | (1ull << OPT_LOOPBACK) |
                       (1ull << OPT_SROUTES) | (1ull << OPT_TCPMSSFIXUP) |
                       (1ull << OPT_THROUGHPUT) | (1ull << OPT_UTMP) |
                       (1ull << OPT_NAS_IP_ADDRESS) |
                       (1ull << OPT_NAS_IDENTIFIER);
#ifndef NOINET6
  opt_enable(&bundle, OPT_IPCP);
  if (probe.ipv6_available)
    opt_enable(&bundle, OPT_IPV6CP);
#endif
  *bundle.cfg.label = '\0';
  bundle.cfg.ifqueue = DEF_IFQUEUE;
  bundle.cfg.choked.timeout = CHOKED_TIMEOUT;
  bundle.phys_type.all = type;
  bundle.phys_type.open = 0;
  bundle.upat = 0;

  bundle.links = datalink_Create("deflink", &bundle, type);
  if (bundle.links == NULL) {
    log_Printf(LogALERT, "Cannot create data link: %s\n", strerror(errno));
    iface_Free(bundle.iface);
    bundle.iface = NULL;
    close(bundle.dev.fd);
    return NULL;
  }

  bundle.desc.type = BUNDLE_DESCRIPTOR;
  bundle.desc.UpdateSet = bundle_UpdateSet;
  bundle.desc.IsSet = bundle_IsSet;
  bundle.desc.Read = bundle_DescriptorRead;
  bundle.desc.Write = bundle_DescriptorWrite;

  ncp_Init(&bundle.ncp, &bundle);

  memset(&bundle.filter, '\0', sizeof bundle.filter);
  bundle.filter.in.fragok = bundle.filter.in.logok = 1;
  bundle.filter.in.name = "IN";
  bundle.filter.out.fragok = bundle.filter.out.logok = 1;
  bundle.filter.out.name = "OUT";
  bundle.filter.dial.name = "DIAL";
  bundle.filter.dial.logok = 1;
  bundle.filter.alive.name = "ALIVE";
  bundle.filter.alive.logok = 1;
  {
    int i;
    for (i = 0; i < MAXFILTERS; i++) {
        bundle.filter.in.rule[i].f_action = A_NONE;
        bundle.filter.out.rule[i].f_action = A_NONE;
        bundle.filter.dial.rule[i].f_action = A_NONE;
        bundle.filter.alive.rule[i].f_action = A_NONE;
    }
  }
  memset(&bundle.idle.timer, '\0', sizeof bundle.idle.timer);
  bundle.idle.done = 0;
  bundle.notify.fd = -1;
  memset(&bundle.choked.timer, '\0', sizeof bundle.choked.timer);
#ifndef NORADIUS
  radius_Init(&bundle.radius);
#endif

  /* Clean out any leftover crud */
  iface_Clear(bundle.iface, &bundle.ncp, 0, IFACE_CLEAR_ALL);

  bundle_LockTun(&bundle);

  return &bundle;
}