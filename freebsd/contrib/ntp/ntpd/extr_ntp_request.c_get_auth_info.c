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
struct req_pkt {int dummy; } ;
struct info_auth {void* timereset; void* expired; void* keyuncached; void* decryptions; void* encryptions; void* keynotfound; void* keylookups; void* numfreekeys; void* numkeys; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  endpt ;

/* Variables and functions */
 scalar_t__ auth_timereset ; 
 scalar_t__ authdecryptions ; 
 scalar_t__ authencryptions ; 
 scalar_t__ authkeyexpired ; 
 scalar_t__ authkeylookups ; 
 scalar_t__ authkeynotfound ; 
 scalar_t__ authkeyuncached ; 
 scalar_t__ authnumfreekeys ; 
 scalar_t__ authnumkeys ; 
 scalar_t__ current_time ; 
 int /*<<< orphan*/  flush_pkt () ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  more_pkt () ; 
 scalar_t__ prepare_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct req_pkt*,int) ; 

__attribute__((used)) static void
get_auth_info(
	sockaddr_u *srcadr,
	endpt *inter,
	struct req_pkt *inpkt
	)
{
	register struct info_auth *ia;

	ia = (struct info_auth *)prepare_pkt(srcadr, inter, inpkt,
					     sizeof(struct info_auth));

	ia->numkeys = htonl((u_int32)authnumkeys);
	ia->numfreekeys = htonl((u_int32)authnumfreekeys);
	ia->keylookups = htonl((u_int32)authkeylookups);
	ia->keynotfound = htonl((u_int32)authkeynotfound);
	ia->encryptions = htonl((u_int32)authencryptions);
	ia->decryptions = htonl((u_int32)authdecryptions);
	ia->keyuncached = htonl((u_int32)authkeyuncached);
	ia->expired = htonl((u_int32)authkeyexpired);
	ia->timereset = htonl((u_int32)(current_time - auth_timereset));
	
	(void) more_pkt();
	flush_pkt();
}