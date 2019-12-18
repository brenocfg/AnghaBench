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
typedef  int /*<<< orphan*/  u_char ;
struct peer {int dummy; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;

/* Variables and functions */
 int /*<<< orphan*/  AF (int /*<<< orphan*/ *) ; 
 struct peer* findexistingpeer_addr (int /*<<< orphan*/ *,struct peer*,int,int /*<<< orphan*/ ,int*) ; 
 struct peer* findexistingpeer_name (char const*,int /*<<< orphan*/ ,struct peer*,int) ; 

struct peer *
findexistingpeer(
	sockaddr_u *	addr,
	const char *	hostname,
	struct peer *	start_peer,
	int		mode,
	u_char		cast_flags,
	int *		ip_count
	)
{
	if (hostname != NULL)
		return findexistingpeer_name(hostname, AF(addr),
					     start_peer, mode);
	else
		return findexistingpeer_addr(addr, start_peer, mode,
					     cast_flags, ip_count);
}