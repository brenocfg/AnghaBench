#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  v6; int /*<<< orphan*/  v4; } ;
struct TYPE_4__ {int /*<<< orphan*/  v6; int /*<<< orphan*/  v4; } ;
struct tcp_fastopen_ccache_entry {scalar_t__ af; int cookie_len; scalar_t__ disable_time; scalar_t__ server_mss; int /*<<< orphan*/  cookie; int /*<<< orphan*/  server_port; TYPE_2__ cce_server_ip; TYPE_1__ cce_client_ip; } ;
struct tcp_fastopen_ccache_bucket {scalar_t__ ccb_num_entries; int /*<<< orphan*/  ccb_entries; } ;
struct in_conninfo {int inc_flags; int /*<<< orphan*/  inc_fport; int /*<<< orphan*/  inc6_faddr; int /*<<< orphan*/  inc6_laddr; int /*<<< orphan*/  inc_faddr; int /*<<< orphan*/  inc_laddr; } ;
struct TYPE_6__ {scalar_t__ bucket_limit; int /*<<< orphan*/  zone; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CCB_LOCK_ASSERT (struct tcp_fastopen_ccache_bucket*) ; 
 int INC_ISIPV6 ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct tcp_fastopen_ccache_entry*,int /*<<< orphan*/ ) ; 
 struct tcp_fastopen_ccache_entry* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tcp_fastopen_ccache_entry*,int /*<<< orphan*/ ) ; 
 int TCP_FASTOPEN_MAX_COOKIE_LEN ; 
 int TCP_FASTOPEN_MIN_COOKIE_LEN ; 
 TYPE_3__ V_tcp_fastopen_ccache ; 
 int /*<<< orphan*/  bucket_entries ; 
 int /*<<< orphan*/  cce_link ; 
 scalar_t__ getsbinuptime () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 struct tcp_fastopen_ccache_entry* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tcp_fastopen_ccache_entry *
tcp_fastopen_ccache_create(struct tcp_fastopen_ccache_bucket *ccb,
    struct in_conninfo *inc, uint16_t mss, uint8_t cookie_len, uint8_t *cookie)
{
	struct tcp_fastopen_ccache_entry *cce;
	
	/*
	 * 1. Create a new entry, or
	 * 2. Reclaim an existing entry, or
	 * 3. Fail
	 */

	CCB_LOCK_ASSERT(ccb);
	
	cce = NULL;
	if (ccb->ccb_num_entries < V_tcp_fastopen_ccache.bucket_limit)
		cce = uma_zalloc(V_tcp_fastopen_ccache.zone, M_NOWAIT);

	if (cce == NULL) {
		/*
		 * At bucket limit, or out of memory - reclaim last
		 * entry in bucket.
		 */
		cce = TAILQ_LAST(&ccb->ccb_entries, bucket_entries);
		if (cce == NULL) {
			/* XXX count this event */
			return (NULL);
		}

		TAILQ_REMOVE(&ccb->ccb_entries, cce, cce_link);
	} else
		ccb->ccb_num_entries++;

	TAILQ_INSERT_HEAD(&ccb->ccb_entries, cce, cce_link);
	cce->af = (inc->inc_flags & INC_ISIPV6) ? AF_INET6 : AF_INET;
	if (cce->af == AF_INET) {
		cce->cce_client_ip.v4 = inc->inc_laddr;
		cce->cce_server_ip.v4 = inc->inc_faddr;
	} else {
		cce->cce_client_ip.v6 = inc->inc6_laddr;
		cce->cce_server_ip.v6 = inc->inc6_faddr;
	}
	cce->server_port = inc->inc_fport;
	if ((cookie_len >= TCP_FASTOPEN_MIN_COOKIE_LEN) &&
	    (cookie_len <= TCP_FASTOPEN_MAX_COOKIE_LEN) &&
	    ((cookie_len & 0x1) == 0)) {
		cce->server_mss = mss;
		cce->cookie_len = cookie_len;
		memcpy(cce->cookie, cookie, cookie_len);
		cce->disable_time = 0;
	} else {
		/* invalid cookie length, disable cce */
		cce->server_mss = 0;
		cce->cookie_len = 0;
		cce->disable_time = getsbinuptime();
	}
	
	return (cce);
}