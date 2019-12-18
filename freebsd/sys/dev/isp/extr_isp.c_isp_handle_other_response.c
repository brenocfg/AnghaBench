#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ispstatusreq_t ;
struct TYPE_16__ {int isp_nchan; } ;
typedef  TYPE_1__ ispsoftc_t ;
typedef  int /*<<< orphan*/  isphdr_t ;
struct TYPE_17__ {int ridacq_vp_port_lo; int* ridacq_map; int ridacq_vp_index; int /*<<< orphan*/  ridacq_vp_status; int /*<<< orphan*/  ridacq_format; int /*<<< orphan*/  ridacq_vp_port_hi; } ;
typedef  TYPE_2__ isp_ridacq_t ;
struct TYPE_18__ {int isp_topo; int isp_portid; void* isp_loopstate; int /*<<< orphan*/  role; } ;
typedef  TYPE_3__ fcparam ;

/* Variables and functions */
 TYPE_3__* FCPARAM (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ISPASYNC_CHANGE_NOTIFY ; 
 int /*<<< orphan*/  ISPASYNC_CHANGE_OTHER ; 
 int /*<<< orphan*/  ISPASYNC_LOOP_DOWN ; 
 int /*<<< orphan*/  ISP_IOXGET_32 (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  ISP_LOG_WARN1 ; 
 int /*<<< orphan*/  ISP_ROLE_NONE ; 
 void* LOOP_HAVE_ADDR ; 
 void* LOOP_HAVE_LINK ; 
 void* LOOP_NIL ; 
 int /*<<< orphan*/  QENTRY_LEN ; 
 int /*<<< orphan*/  RIDACQ_STS_CHANGED ; 
 int /*<<< orphan*/  RIDACQ_STS_COMPLETE ; 
#define  RQSTYPE_ABTS_RCVD 145 
#define  RQSTYPE_ABTS_RSP 144 
#define  RQSTYPE_ATIO 143 
#define  RQSTYPE_ATIO2 142 
#define  RQSTYPE_CTIO 141 
#define  RQSTYPE_CTIO1 140 
#define  RQSTYPE_CTIO2 139 
#define  RQSTYPE_CTIO3 138 
#define  RQSTYPE_CTIO7 137 
#define  RQSTYPE_CT_PASSTHRU 136 
#define  RQSTYPE_LOGIN 135 
#define  RQSTYPE_MARKER 134 
#define  RQSTYPE_NOTIFY 133 
#define  RQSTYPE_NOTIFY_ACK 132 
#define  RQSTYPE_REQUEST 131 
#define  RQSTYPE_RPT_ID_ACQ 130 
#define  RQSTYPE_VP_CTRL 129 
#define  RQSTYPE_VP_MODIFY 128 
 int /*<<< orphan*/  isp_async (TYPE_1__*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  isp_destroy_handle (TYPE_1__*,int) ; 
 void* isp_find_xs (TYPE_1__*,int) ; 
 int /*<<< orphan*/  isp_get_ridacq (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  isp_prt (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int isp_target_notify (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (void*) ; 

__attribute__((used)) static int
isp_handle_other_response(ispsoftc_t *isp, int type, isphdr_t *hp, uint32_t *optrp)
{
	isp_ridacq_t rid;
	int chan, c;
	uint32_t hdl, portid;
	void *ptr;

	switch (type) {
	case RQSTYPE_MARKER:
		isp_prt(isp, ISP_LOG_WARN1, "Marker Response");
		return (1);
	case RQSTYPE_RPT_ID_ACQ:
		isp_get_ridacq(isp, (isp_ridacq_t *)hp, &rid);
		portid = (uint32_t)rid.ridacq_vp_port_hi << 16 |
		    rid.ridacq_vp_port_lo;
		if (rid.ridacq_format == 0) {
			for (chan = 0; chan < isp->isp_nchan; chan++) {
				fcparam *fcp = FCPARAM(isp, chan);
				if (fcp->role == ISP_ROLE_NONE)
					continue;
				c = (chan == 0) ? 127 : (chan - 1);
				if (rid.ridacq_map[c / 16] & (1 << (c % 16)) ||
				    chan == 0) {
					fcp->isp_loopstate = LOOP_HAVE_LINK;
					isp_async(isp, ISPASYNC_CHANGE_NOTIFY,
					    chan, ISPASYNC_CHANGE_OTHER);
				} else {
					fcp->isp_loopstate = LOOP_NIL;
					isp_async(isp, ISPASYNC_LOOP_DOWN,
					    chan);
				}
			}
		} else {
			fcparam *fcp = FCPARAM(isp, rid.ridacq_vp_index);
			if (rid.ridacq_vp_status == RIDACQ_STS_COMPLETE ||
			    rid.ridacq_vp_status == RIDACQ_STS_CHANGED) {
				fcp->isp_topo = (rid.ridacq_map[0] >> 9) & 0x7;
				fcp->isp_portid = portid;
				fcp->isp_loopstate = LOOP_HAVE_ADDR;
				isp_async(isp, ISPASYNC_CHANGE_NOTIFY,
				    rid.ridacq_vp_index, ISPASYNC_CHANGE_OTHER);
			} else {
				fcp->isp_loopstate = LOOP_NIL;
				isp_async(isp, ISPASYNC_LOOP_DOWN,
				    rid.ridacq_vp_index);
			}
		}
		return (1);
	case RQSTYPE_CT_PASSTHRU:
	case RQSTYPE_VP_MODIFY:
	case RQSTYPE_VP_CTRL:
	case RQSTYPE_LOGIN:
		ISP_IOXGET_32(isp, (uint32_t *)(hp + 1), hdl);
		ptr = isp_find_xs(isp, hdl);
		if (ptr != NULL) {
			isp_destroy_handle(isp, hdl);
			memcpy(ptr, hp, QENTRY_LEN);
			wakeup(ptr);
		}
		return (1);
	case RQSTYPE_ATIO:
	case RQSTYPE_CTIO:
	case RQSTYPE_NOTIFY:
	case RQSTYPE_NOTIFY_ACK:
	case RQSTYPE_CTIO1:
	case RQSTYPE_ATIO2:
	case RQSTYPE_CTIO2:
	case RQSTYPE_CTIO3:
	case RQSTYPE_CTIO7:
	case RQSTYPE_ABTS_RCVD:
	case RQSTYPE_ABTS_RSP:
#ifdef	ISP_TARGET_MODE
		return (isp_target_notify(isp, (ispstatusreq_t *) hp, optrp));
#endif
		/* FALLTHROUGH */
	case RQSTYPE_REQUEST:
	default:
		return (0);
	}
}