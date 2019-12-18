#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct daemon {int use_response_ip; TYPE_2__** workers; scalar_t__ need_to_exit; int /*<<< orphan*/ * ports; TYPE_4__* cfg; int /*<<< orphan*/  mods; TYPE_1__* env; int /*<<< orphan*/  respip_set; int /*<<< orphan*/  views; int /*<<< orphan*/  local_zones; int /*<<< orphan*/  dnscenv; int /*<<< orphan*/  tcl; int /*<<< orphan*/  acl; } ;
struct TYPE_16__ {scalar_t__ dnscrypt; } ;
struct TYPE_15__ {scalar_t__ need_to_exit; } ;
struct TYPE_14__ {int /*<<< orphan*/  auth_zones; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKAGE_STRING ; 
 int /*<<< orphan*/  acl_list_apply_cfg (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_zones_apply_cfg (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  daemon_create_workers (struct daemon*) ; 
 int /*<<< orphan*/  daemon_setup_modules (struct daemon*) ; 
 int /*<<< orphan*/  daemon_start_others (struct daemon*) ; 
 int /*<<< orphan*/  daemon_stop_others (struct daemon*) ; 
 int /*<<< orphan*/  dnsc_apply_cfg (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  dnsc_create () ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  local_zones_apply_cfg (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  local_zones_create () ; 
 int /*<<< orphan*/  log_assert (struct daemon*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 scalar_t__ modstack_find (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  respip_global_apply_cfg (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  respip_set_create () ; 
 int /*<<< orphan*/  respip_set_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  respip_views_apply_cfg (int /*<<< orphan*/ ,TYPE_4__*,int*) ; 
 int /*<<< orphan*/  sd_notify (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shm_main_init (struct daemon*) ; 
 int /*<<< orphan*/  shm_main_shutdown (struct daemon*) ; 
 int /*<<< orphan*/  signal_handling_playback (TYPE_2__*) ; 
 int /*<<< orphan*/  tcl_list_apply_cfg (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  views_apply_cfg (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  views_create () ; 
 int /*<<< orphan*/  worker_init (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  worker_work (TYPE_2__*) ; 

void 
daemon_fork(struct daemon* daemon)
{
	int have_view_respip_cfg = 0;

	log_assert(daemon);
	if(!(daemon->views = views_create()))
		fatal_exit("Could not create views: out of memory");
	/* create individual views and their localzone/data trees */
	if(!views_apply_cfg(daemon->views, daemon->cfg))
		fatal_exit("Could not set up views");

	if(!acl_list_apply_cfg(daemon->acl, daemon->cfg, daemon->views))
		fatal_exit("Could not setup access control list");
	if(!tcl_list_apply_cfg(daemon->tcl, daemon->cfg))
		fatal_exit("Could not setup TCP connection limits");
	if(daemon->cfg->dnscrypt) {
#ifdef USE_DNSCRYPT
		daemon->dnscenv = dnsc_create();
		if (!daemon->dnscenv)
			fatal_exit("dnsc_create failed");
		dnsc_apply_cfg(daemon->dnscenv, daemon->cfg);
#else
		fatal_exit("dnscrypt enabled in config but unbound was not built with "
				   "dnscrypt support");
#endif
	}
	/* create global local_zones */
	if(!(daemon->local_zones = local_zones_create()))
		fatal_exit("Could not create local zones: out of memory");
	if(!local_zones_apply_cfg(daemon->local_zones, daemon->cfg))
		fatal_exit("Could not set up local zones");

	/* process raw response-ip configuration data */
	if(!(daemon->respip_set = respip_set_create()))
		fatal_exit("Could not create response IP set");
	if(!respip_global_apply_cfg(daemon->respip_set, daemon->cfg))
		fatal_exit("Could not set up response IP set");
	if(!respip_views_apply_cfg(daemon->views, daemon->cfg,
		&have_view_respip_cfg))
		fatal_exit("Could not set up per-view response IP sets");
	daemon->use_response_ip = !respip_set_is_empty(daemon->respip_set) ||
		have_view_respip_cfg;
	
	/* read auth zonefiles */
	if(!auth_zones_apply_cfg(daemon->env->auth_zones, daemon->cfg, 1))
		fatal_exit("auth_zones could not be setup");

	/* setup modules */
	daemon_setup_modules(daemon);

	/* response-ip-xxx options don't work as expected without the respip
	 * module.  To avoid run-time operational surprise we reject such
	 * configuration. */
	if(daemon->use_response_ip &&
		modstack_find(&daemon->mods, "respip") < 0)
		fatal_exit("response-ip options require respip module");

	/* first create all the worker structures, so we can pass
	 * them to the newly created threads. 
	 */
	daemon_create_workers(daemon);

#if defined(HAVE_EV_LOOP) || defined(HAVE_EV_DEFAULT_LOOP)
	/* in libev the first inited base gets signals */
	if(!worker_init(daemon->workers[0], daemon->cfg, daemon->ports[0], 1))
		fatal_exit("Could not initialize main thread");
#endif
	
	/* Now create the threads and init the workers.
	 * By the way, this is thread #0 (the main thread).
	 */
	daemon_start_others(daemon);

	/* Special handling for the main thread. This is the thread
	 * that handles signals and remote control.
	 */
#if !(defined(HAVE_EV_LOOP) || defined(HAVE_EV_DEFAULT_LOOP))
	/* libevent has the last inited base get signals (or any base) */
	if(!worker_init(daemon->workers[0], daemon->cfg, daemon->ports[0], 1))
		fatal_exit("Could not initialize main thread");
#endif
	signal_handling_playback(daemon->workers[0]);

	if (!shm_main_init(daemon))
		log_warn("SHM has failed");

	/* Start resolver service on main thread. */
#ifdef HAVE_SYSTEMD
	sd_notify(0, "READY=1");
#endif
	log_info("start of service (%s).", PACKAGE_STRING);
	worker_work(daemon->workers[0]);
#ifdef HAVE_SYSTEMD
	if (daemon->workers[0]->need_to_exit)
		sd_notify(0, "STOPPING=1");
	else
		sd_notify(0, "RELOADING=1");
#endif
	log_info("service stopped (%s).", PACKAGE_STRING);

	/* we exited! a signal happened! Stop other threads */
	daemon_stop_others(daemon);

	/* Shutdown SHM */
	shm_main_shutdown(daemon);

	daemon->need_to_exit = daemon->workers[0]->need_to_exit;
}