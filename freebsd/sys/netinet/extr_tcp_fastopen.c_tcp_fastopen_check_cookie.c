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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct rm_priotracker {int dummy; } ;
struct in_conninfo {int dummy; } ;
struct TYPE_2__ {size_t newest; int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 unsigned int TCP_FASTOPEN_COOKIE_LEN ; 
 int /*<<< orphan*/  TCP_FASTOPEN_KEYS_RLOCK (struct rm_priotracker*) ; 
 int /*<<< orphan*/  TCP_FASTOPEN_KEYS_RUNLOCK (struct rm_priotracker*) ; 
 int TCP_FASTOPEN_MAX_KEYS ; 
 scalar_t__ V_tcp_fastopen_acceptany ; 
 TYPE_1__ V_tcp_fastopen_keys ; 
 unsigned int V_tcp_fastopen_numkeys ; 
 int tcp_fastopen_find_cookie_match_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_fastopen_make_cookie (int /*<<< orphan*/ ,struct in_conninfo*) ; 

int
tcp_fastopen_check_cookie(struct in_conninfo *inc, uint8_t *cookie,
    unsigned int len, uint64_t *latest_cookie)
{
	struct rm_priotracker tracker;
	unsigned int i, key_index;
	int rv;
	uint64_t cur_cookie;

	if (V_tcp_fastopen_acceptany) {
		*latest_cookie = 0;
		return (1);
	}

	TCP_FASTOPEN_KEYS_RLOCK(&tracker);
	if (len != TCP_FASTOPEN_COOKIE_LEN) {
		if (V_tcp_fastopen_numkeys > 0) {
			*latest_cookie =
			    tcp_fastopen_make_cookie(
				V_tcp_fastopen_keys.key[V_tcp_fastopen_keys.newest],
				inc);
			rv = 0;
		} else
			rv = -1;
		goto out;
	}

	/*
	 * Check against each available key, from newest to oldest.
	 */
	key_index = V_tcp_fastopen_keys.newest;
	for (i = 0; i < V_tcp_fastopen_numkeys; i++) {
		cur_cookie =
		    tcp_fastopen_make_cookie(V_tcp_fastopen_keys.key[key_index],
			inc);
		if (i == 0)
			*latest_cookie = cur_cookie;
		rv = tcp_fastopen_find_cookie_match_locked(cookie, &cur_cookie);
		if (rv)
			goto out;
		if (key_index == 0)
			key_index = TCP_FASTOPEN_MAX_KEYS - 1;
		else
			key_index--;
	}
	rv = 0;

 out:
	TCP_FASTOPEN_KEYS_RUNLOCK(&tracker);
	return (rv);
}