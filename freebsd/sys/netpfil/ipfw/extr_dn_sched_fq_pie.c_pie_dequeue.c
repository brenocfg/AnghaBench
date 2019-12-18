#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pie_status {int sflags; int dq_count; long measurement_start; long avg_dq_time; long current_qdelay; struct dn_aqm_pie_parms* parms; } ;
struct TYPE_3__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct fq_pie_si {int dummy; } ;
struct TYPE_4__ {int len_bytes; } ;
struct fq_pie_flow {TYPE_2__ stats; struct pie_status pst; } ;
struct dn_aqm_pie_parms {int flags; } ;
typedef  long int32_t ;
typedef  long aqm_time_t ;

/* Variables and functions */
 long AQM_UNOW ; 
 int PIE_ACTIVE ; 
 int PIE_DEPRATEEST_ENABLED ; 
 int PIE_DQ_THRESHOLD ; 
 int PIE_INMEASUREMENT ; 
 struct mbuf* fq_pie_extract_head (struct fq_pie_flow*,long*,struct fq_pie_si*,int) ; 

__attribute__((used)) static struct mbuf *
pie_dequeue(struct fq_pie_flow *q, struct fq_pie_si *si)
{
	struct mbuf *m;
	struct dn_aqm_pie_parms *pprms;
	struct pie_status *pst;
	aqm_time_t now;
	aqm_time_t pkt_ts, dq_time;
	int32_t w;

	pst  = &q->pst;
	pprms = q->pst.parms;

	/*we extarct packet ts only when Departure Rate Estimation dis not used*/
	m = fq_pie_extract_head(q, &pkt_ts, si, 
		!(pprms->flags & PIE_DEPRATEEST_ENABLED));
	
	if (!m || !(pst->sflags & PIE_ACTIVE))
		return m;

	now = AQM_UNOW;
	if (pprms->flags & PIE_DEPRATEEST_ENABLED) {
		/* calculate average depature time */
		if(pst->sflags & PIE_INMEASUREMENT) {
			pst->dq_count += m->m_pkthdr.len;

			if (pst->dq_count >= PIE_DQ_THRESHOLD) {
				dq_time = now - pst->measurement_start;

				/* 
				 * if we don't have old avg dq_time i.e PIE is (re)initialized, 
				 * don't use weight to calculate new avg_dq_time
				 */
				if(pst->avg_dq_time == 0)
					pst->avg_dq_time = dq_time;
				else {
					/* 
					 * weight = PIE_DQ_THRESHOLD/2^6, but we scaled 
					 * weight by 2^8. Thus, scaled 
					 * weight = PIE_DQ_THRESHOLD /2^8 
					 * */
					w = PIE_DQ_THRESHOLD >> 8;
					pst->avg_dq_time = (dq_time* w
						+ (pst->avg_dq_time * ((1L << 8) - w))) >> 8;
					pst->sflags &= ~PIE_INMEASUREMENT;
				}
			}
		}

		/* 
		 * Start new measurment cycle when the queue has
		 *  PIE_DQ_THRESHOLD worth of bytes.
		 */
		if(!(pst->sflags & PIE_INMEASUREMENT) && 
			q->stats.len_bytes >= PIE_DQ_THRESHOLD) {
			pst->sflags |= PIE_INMEASUREMENT;
			pst->measurement_start = now;
			pst->dq_count = 0;
		}
	}
	/* Optionally, use packet timestamp to estimate queue delay */
	else
		pst->current_qdelay = now - pkt_ts;

	return m;	
}