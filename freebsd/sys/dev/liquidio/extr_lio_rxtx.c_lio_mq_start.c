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
typedef  int uint32_t ;
struct octeon_device {int num_iqs; struct lio_instr_queue** instr_queue; } ;
struct TYPE_2__ {int flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct lio_instr_queue {int /*<<< orphan*/  enq_lock; int /*<<< orphan*/  br; } ;
struct lio {struct octeon_device* oct_dev; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 int curcpu ; 
 int drbr_enqueue (struct ifnet*,int /*<<< orphan*/ ,struct mbuf*) ; 
 struct lio* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*,int,int) ; 
 int /*<<< orphan*/  lio_mq_start_locked (struct ifnet*,struct lio_instr_queue*) ; 
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rss_hash2bucket (int,scalar_t__,int*) ; 

int
lio_mq_start(struct ifnet *ifp, struct mbuf *m)
{
	struct lio		*lio = if_getsoftc(ifp);
	struct octeon_device	*oct = lio->oct_dev;
	struct lio_instr_queue	*iq;
	int	err = 0, i;
#ifdef RSS
	uint32_t	bucket_id;
#endif

	if (M_HASHTYPE_GET(m) != M_HASHTYPE_NONE) {
#ifdef RSS
		if (rss_hash2bucket(m->m_pkthdr.flowid, M_HASHTYPE_GET(m),
				    &bucket_id) == 0) {
			i = bucket_id % oct->num_iqs;
			if (bucket_id > oct->num_iqs)
				lio_dev_dbg(oct,
					    "bucket_id (%d) > num_iqs (%d)\n",
					    bucket_id, oct->num_iqs);
		} else
#endif
			i = m->m_pkthdr.flowid % oct->num_iqs;
	} else
		i = curcpu % oct->num_iqs;

	iq = oct->instr_queue[i];

	err = drbr_enqueue(ifp, iq->br, m);
	if (err)
		return (err);

	if (mtx_trylock(&iq->enq_lock)) {
		lio_mq_start_locked(ifp, iq);
		mtx_unlock(&iq->enq_lock);
	}

	return (err);
}