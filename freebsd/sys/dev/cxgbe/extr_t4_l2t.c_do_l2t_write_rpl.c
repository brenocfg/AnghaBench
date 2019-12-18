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
struct sge_iq {int dummy; } ;
struct rss_header {int dummy; } ;
struct mbuf {int dummy; } ;
struct cpl_l2t_write_rpl {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ CPL_ERR_NONE ; 
 int EINVAL ; 
 unsigned int GET_TID (struct cpl_l2t_write_rpl const*) ; 
 unsigned int L2T_SIZE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,scalar_t__,unsigned int) ; 

int
do_l2t_write_rpl(struct sge_iq *iq, const struct rss_header *rss,
    struct mbuf *m)
{
	const struct cpl_l2t_write_rpl *rpl = (const void *)(rss + 1);
	unsigned int tid = GET_TID(rpl);
	unsigned int idx = tid % L2T_SIZE;

	if (__predict_false(rpl->status != CPL_ERR_NONE)) {
		log(LOG_ERR,
		    "Unexpected L2T_WRITE_RPL (%u) for entry at hw_idx %u\n",
		    rpl->status, idx);
		return (EINVAL);
	}

	return (0);
}