#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32 ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int u_char ;
struct peer {int dummy; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  keyid_t ;
typedef  int /*<<< orphan*/  endpt ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_CONFIG ; 
 int /*<<< orphan*/  FLAG_IBURST ; 
 int /*<<< orphan*/  FLAG_PREEMPT ; 
 int /*<<< orphan*/  IS_MCAST (int /*<<< orphan*/ *) ; 
 int MDF_ACAST ; 
 int MDF_BCAST ; 
 int MDF_MCAST ; 
 int MDF_POOL ; 
 int MDF_UCAST ; 
#define  MODE_BROADCAST 129 
#define  MODE_CLIENT 128 
 int /*<<< orphan*/  SOCK_UNSPEC (int /*<<< orphan*/ *) ; 
 scalar_t__ mode_ntpdate ; 
 struct peer* newpeer (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

struct peer *
peer_config(
	sockaddr_u *	srcadr,
	const char *	hostname,
	endpt *		dstadr,
	int		ippeerlimit,
	u_char		hmode,
	u_char		version,
	u_char		minpoll,
	u_char		maxpoll,
	u_int		flags,
	u_int32		ttl,
	keyid_t		key,
	const char *	ident		/* autokey group */
	)
{
	u_char cast_flags;

	/*
	 * We do a dirty little jig to figure the cast flags. This is
	 * probably not the best place to do this, at least until the
	 * configure code is rebuilt. Note only one flag can be set.
	 */
	switch (hmode) {
	case MODE_BROADCAST:
		if (IS_MCAST(srcadr))
			cast_flags = MDF_MCAST;
		else
			cast_flags = MDF_BCAST;
		break;

	case MODE_CLIENT:
		if (hostname != NULL && SOCK_UNSPEC(srcadr))
			cast_flags = MDF_POOL;
		else if (IS_MCAST(srcadr))
			cast_flags = MDF_ACAST;
		else
			cast_flags = MDF_UCAST;
		break;

	default:
		cast_flags = MDF_UCAST;
	}

	/*
	 * Mobilize the association and initialize its variables. If
	 * emulating ntpdate, force iburst.  For pool and manycastclient
	 * strip FLAG_PREEMPT as the prototype associations are not
	 * themselves preemptible, though the resulting associations
	 * are.
	 */
	flags |= FLAG_CONFIG;
	if (mode_ntpdate)
		flags |= FLAG_IBURST;
	if ((MDF_ACAST | MDF_POOL) & cast_flags)
		flags &= ~FLAG_PREEMPT;
	return newpeer(srcadr, hostname, dstadr, ippeerlimit, hmode, version,
	    minpoll, maxpoll, flags, cast_flags, ttl, key, ident);
}