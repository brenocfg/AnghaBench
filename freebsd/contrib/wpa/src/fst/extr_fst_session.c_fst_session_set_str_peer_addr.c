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
typedef  int /*<<< orphan*/  u8 ;
struct fst_session {int dummy; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int ETH_ALEN ; 
 int fst_read_peer_addr (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fst_session_set_peer_addr (struct fst_session*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int fst_session_set_str_peer_addr(struct fst_session *s, const char *mac,
				  Boolean is_old)
{
	u8 peer_addr[ETH_ALEN];
	int res = fst_read_peer_addr(mac, peer_addr);

	if (res)
		return res;

	fst_session_set_peer_addr(s, peer_addr, is_old);

	return 0;
}