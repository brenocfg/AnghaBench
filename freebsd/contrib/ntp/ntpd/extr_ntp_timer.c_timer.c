#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int /*<<< orphan*/  time_t ;
struct peer {int flags; scalar_t__ throttle; int nextdate; struct peer* p_link; } ;
struct TYPE_3__ {int /*<<< orphan*/  l_ui; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int FLAG_REFCLOCK ; 
 scalar_t__ HUFFPUFF ; 
 int /*<<< orphan*/  LEAP_ADDSECOND ; 
 int /*<<< orphan*/  LEAP_DELSECOND ; 
 scalar_t__ LEAP_NOTINSYNC ; 
 int /*<<< orphan*/  LEAP_NOWARNING ; 
 int /*<<< orphan*/  LOOPBACKADR ; 
 scalar_t__ LSPROX_ANNOUNCE ; 
 scalar_t__ LSPROX_NOWARN ; 
 int /*<<< orphan*/  RAND_bytes (int*,int) ; 
 scalar_t__ SECSPERDAY ; 
 scalar_t__ SECSPERHR ; 
 scalar_t__ STRATUM_UNSPEC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  adj_host_clock () ; 
 int adjust_timer ; 
 int /*<<< orphan*/  auth_agekeys () ; 
 int /*<<< orphan*/  check_leap_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_leapsec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ crypto_flags ; 
 int /*<<< orphan*/  crypto_update () ; 
 int current_time ; 
 int /*<<< orphan*/  get_systime (TYPE_1__*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  huffpuff () ; 
 int huffpuff_timer ; 
 scalar_t__ interface_interval ; 
 int interface_timer ; 
 int /*<<< orphan*/  interface_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int keys_timer ; 
 scalar_t__ leapdif ; 
 int leapf_timer ; 
 scalar_t__ leapsec ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int orphwait ; 
 struct peer* peer_list ; 
 int /*<<< orphan*/  refclock_timer (struct peer*) ; 
 int /*<<< orphan*/  refclock_transmit (struct peer*) ; 
 int revoke_timer ; 
 int /*<<< orphan*/  set_sys_leap (int /*<<< orphan*/ ) ; 
 int stats_timer ; 
 unsigned long sys_automax ; 
 scalar_t__ sys_leap ; 
 scalar_t__ sys_offset ; 
 scalar_t__ sys_orphan ; 
 int /*<<< orphan*/ * sys_peer ; 
 int /*<<< orphan*/  sys_private ; 
 int /*<<< orphan*/  sys_refid ; 
 unsigned long sys_revoke ; 
 scalar_t__ sys_rootdelay ; 
 scalar_t__ sys_rootdisp ; 
 int sys_stratum ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_interfacetimeout (scalar_t__) ; 
 int /*<<< orphan*/  transmit (struct peer*) ; 
 int worker_idle_timer ; 
 int /*<<< orphan*/  worker_idle_timer_fired () ; 
 int /*<<< orphan*/  write_stats () ; 

void
timer(void)
{
	struct peer *	p;
	struct peer *	next_peer;
	l_fp		now;
	time_t          tnow;

	/*
	 * The basic timerevent is one second.  This is used to adjust the
	 * system clock in time and frequency, implement the kiss-o'-death
	 * function and the association polling function.
	 */
	current_time++;
	if (adjust_timer <= current_time) {
		adjust_timer += 1;
		adj_host_clock();
#ifdef REFCLOCK
		for (p = peer_list; p != NULL; p = next_peer) {
			next_peer = p->p_link;
			if (FLAG_REFCLOCK & p->flags)
				refclock_timer(p);
		}
#endif /* REFCLOCK */
	}

	/*
	 * Now dispatch any peers whose event timer has expired. Be
	 * careful here, since the peer structure might go away as the
	 * result of the call.
	 */
	for (p = peer_list; p != NULL; p = next_peer) {
		next_peer = p->p_link;

		/*
		 * Restrain the non-burst packet rate not more
		 * than one packet every 16 seconds. This is
		 * usually tripped using iburst and minpoll of
		 * 128 s or less.
		 */
		if (p->throttle > 0)
			p->throttle--;
		if (p->nextdate <= current_time) {
#ifdef REFCLOCK
			if (FLAG_REFCLOCK & p->flags)
				refclock_transmit(p);
			else
#endif	/* REFCLOCK */
				transmit(p);
		}
	}

	/*
	 * Orphan mode is active when enabled and when no servers less
	 * than the orphan stratum are available. A server with no other
	 * synchronization source is an orphan. It shows offset zero and
	 * reference ID the loopback address.
	 */
	if (sys_orphan < STRATUM_UNSPEC && sys_peer == NULL &&
	    current_time > orphwait) {
		if (sys_leap == LEAP_NOTINSYNC) {
			set_sys_leap(LEAP_NOWARNING);
#ifdef AUTOKEY
			if (crypto_flags)
				crypto_update();
#endif	/* AUTOKEY */
		}
		sys_stratum = (u_char)sys_orphan;
		if (sys_stratum > 1)
			sys_refid = htonl(LOOPBACKADR);
		else
			memcpy(&sys_refid, "LOOP", 4);
		sys_offset = 0;
		sys_rootdelay = 0;
		sys_rootdisp = 0;
	}

	get_systime(&now);
	time(&tnow);

	/*
	 * Leapseconds. Get time and defer to worker if either something
	 * is imminent or every 8th second.
	 */
	if (leapsec > LSPROX_NOWARN || 0 == (current_time & 7))
		check_leapsec(now.l_ui, &tnow,
                                (sys_leap == LEAP_NOTINSYNC));
        if (sys_leap != LEAP_NOTINSYNC) {
                if (leapsec >= LSPROX_ANNOUNCE && leapdif) {
		        if (leapdif > 0)
			        set_sys_leap(LEAP_ADDSECOND);
		        else
			        set_sys_leap(LEAP_DELSECOND);
                } else {
                        set_sys_leap(LEAP_NOWARNING);
                }
	}

	/*
	 * Update huff-n'-puff filter.
	 */
	if (huffpuff_timer <= current_time) {
		huffpuff_timer += HUFFPUFF;
		huffpuff();
	}

#ifdef AUTOKEY
	/*
	 * Garbage collect expired keys.
	 */
	if (keys_timer <= current_time) {
		keys_timer += (1UL << sys_automax);
		auth_agekeys();
	}

	/*
	 * Generate new private value. This causes all associations
	 * to regenerate cookies.
	 */
	if (revoke_timer && revoke_timer <= current_time) {
		revoke_timer += (1UL << sys_revoke);
		RAND_bytes((u_char *)&sys_private, 4);
	}
#endif	/* AUTOKEY */

	/*
	 * Interface update timer
	 */
	if (interface_interval && interface_timer <= current_time) {
		timer_interfacetimeout(current_time +
		    interface_interval);
		DPRINTF(2, ("timer: interface update\n"));
		interface_update(NULL, NULL);
	}

	if (worker_idle_timer && worker_idle_timer <= current_time)
		worker_idle_timer_fired();

	/*
	 * Finally, write hourly stats and do the hourly
	 * and daily leapfile checks.
	 */
	if (stats_timer <= current_time) {
		stats_timer += SECSPERHR;
		write_stats();
		if (leapf_timer <= current_time) {
			leapf_timer += SECSPERDAY;
			check_leap_file(TRUE, now.l_ui, &tnow);
		} else {
			check_leap_file(FALSE, now.l_ui, &tnow);
		}
	}
}