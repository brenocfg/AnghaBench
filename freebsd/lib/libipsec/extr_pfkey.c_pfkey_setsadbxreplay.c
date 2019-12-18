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
typedef  int uint32_t ;
typedef  int u_int ;
struct sadb_x_sa_replay {int sadb_x_sa_replay_replay; int /*<<< orphan*/  sadb_x_sa_replay_exttype; int /*<<< orphan*/  sadb_x_sa_replay_len; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PFKEY_UNIT64 (int) ; 
 int /*<<< orphan*/  SADB_X_EXT_SA_REPLAY ; 
 int /*<<< orphan*/  memset (struct sadb_x_sa_replay*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static caddr_t
pfkey_setsadbxreplay(caddr_t buf, caddr_t lim, uint32_t wsize)
{
	struct sadb_x_sa_replay *p;
	u_int len;

	p = (struct sadb_x_sa_replay *)buf;
	len = sizeof(struct sadb_x_sa_replay);

	if (buf + len > lim)
		return (NULL);

	memset(p, 0, len);
	p->sadb_x_sa_replay_len = PFKEY_UNIT64(len);
	p->sadb_x_sa_replay_exttype = SADB_X_EXT_SA_REPLAY;
	/* Convert wsize from bytes to number of packets. */
	p->sadb_x_sa_replay_replay = wsize << 3;

	return (buf + len);
}