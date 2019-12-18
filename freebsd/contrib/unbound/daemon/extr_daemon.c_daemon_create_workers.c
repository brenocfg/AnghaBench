#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct worker {int dummy; } ;
struct daemon {int num; struct worker** workers; TYPE_1__* cfg; int /*<<< orphan*/  dtenv; scalar_t__ num_ports; scalar_t__ reuseport; int /*<<< orphan*/  rand; } ;
struct TYPE_2__ {int num_threads; int /*<<< orphan*/  dnstap_socket_path; scalar_t__ dnstap; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ calloc (size_t,int) ; 
 int daemon_get_shufport (struct daemon*,int*) ; 
 int /*<<< orphan*/  dt_apply_cfg (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dt_create (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  hash_set_raninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_warn (char*,int,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ub_initstate (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ ub_random (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int) ; 
 struct worker* worker_create (struct daemon*,int,int*,int) ; 

__attribute__((used)) static void 
daemon_create_workers(struct daemon* daemon)
{
	int i, numport;
	int* shufport;
	log_assert(daemon && daemon->cfg);
	if(!daemon->rand) {
		unsigned int seed = (unsigned int)time(NULL) ^ 
			(unsigned int)getpid() ^ 0x438;
		daemon->rand = ub_initstate(seed, NULL);
		if(!daemon->rand)
			fatal_exit("could not init random generator");
		hash_set_raninit((uint32_t)ub_random(daemon->rand));
	}
	shufport = (int*)calloc(65536, sizeof(int));
	if(!shufport)
		fatal_exit("out of memory during daemon init");
	numport = daemon_get_shufport(daemon, shufport);
	verbose(VERB_ALGO, "total of %d outgoing ports available", numport);
	
	daemon->num = (daemon->cfg->num_threads?daemon->cfg->num_threads:1);
	if(daemon->reuseport && (int)daemon->num < (int)daemon->num_ports) {
		log_warn("cannot reduce num-threads to %d because so-reuseport "
			"so continuing with %d threads.", (int)daemon->num,
			(int)daemon->num_ports);
		daemon->num = (int)daemon->num_ports;
	}
	daemon->workers = (struct worker**)calloc((size_t)daemon->num, 
		sizeof(struct worker*));
	if(!daemon->workers)
		fatal_exit("out of memory during daemon init");
	if(daemon->cfg->dnstap) {
#ifdef USE_DNSTAP
		daemon->dtenv = dt_create(daemon->cfg->dnstap_socket_path,
			(unsigned int)daemon->num);
		if (!daemon->dtenv)
			fatal_exit("dt_create failed");
		dt_apply_cfg(daemon->dtenv, daemon->cfg);
#else
		fatal_exit("dnstap enabled in config but not built with dnstap support");
#endif
	}
	for(i=0; i<daemon->num; i++) {
		if(!(daemon->workers[i] = worker_create(daemon, i,
			shufport+numport*i/daemon->num, 
			numport*(i+1)/daemon->num - numport*i/daemon->num)))
			/* the above is not ports/numthr, due to rounding */
			fatal_exit("could not create worker");
	}
	free(shufport);
}