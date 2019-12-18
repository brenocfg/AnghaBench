#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  u64q_t ;
typedef  int /*<<< orphan*/  u32q_t ;
struct TYPE_13__ {int /*<<< orphan*/  uq64; int /*<<< orphan*/  sq64; } ;
struct TYPE_12__ {int /*<<< orphan*/  uq32; int /*<<< orphan*/  sq32; } ;
struct TYPE_11__ {int /*<<< orphan*/  ulong; int /*<<< orphan*/  slong; } ;
struct TYPE_10__ {int /*<<< orphan*/  u64; int /*<<< orphan*/  s64; } ;
struct TYPE_9__ {int /*<<< orphan*/  u32; int /*<<< orphan*/  s32; } ;
struct voistatdata {TYPE_5__ q64; TYPE_4__ q32; TYPE_3__ intlong; TYPE_2__ int64; TYPE_1__ int32; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  s64q_t ;
typedef  int /*<<< orphan*/  s32q_t ;
typedef  int /*<<< orphan*/  qstr ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  enum vsd_dtype { ____Placeholder_vsd_dtype } vsd_dtype ;
typedef  enum sb_str_fmt { ____Placeholder_sb_str_fmt } sb_str_fmt ;
struct TYPE_14__ {int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 TYPE_6__* CONSTVSD (int /*<<< orphan*/ ,struct voistatdata const*) ; 
 int EINVAL ; 
 int Q_MAXSTRLEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_TOSTR (int /*<<< orphan*/ ,int,int,char*,int) ; 
#define  SB_STRFMT_FREEFORM 148 
#define  SB_STRFMT_JSON 147 
 int SB_STRFMT_NUM_FMTS ; 
#define  VSD_DTYPE_CRHIST32 146 
#define  VSD_DTYPE_CRHIST64 145 
#define  VSD_DTYPE_DRHIST32 144 
#define  VSD_DTYPE_DRHIST64 143 
#define  VSD_DTYPE_DVHIST32 142 
#define  VSD_DTYPE_DVHIST64 141 
#define  VSD_DTYPE_INT_S32 140 
#define  VSD_DTYPE_INT_S64 139 
#define  VSD_DTYPE_INT_SLONG 138 
#define  VSD_DTYPE_INT_U32 137 
#define  VSD_DTYPE_INT_U64 136 
#define  VSD_DTYPE_INT_ULONG 135 
#define  VSD_DTYPE_Q_S32 134 
#define  VSD_DTYPE_Q_S64 133 
#define  VSD_DTYPE_Q_U32 132 
#define  VSD_DTYPE_Q_U64 131 
#define  VSD_DTYPE_TDGSTCLUST32 130 
#define  VSD_DTYPE_TDGSTCLUST64 129 
#define  VSD_DTYPE_VOISTATE 128 
 int VSD_NUM_DTYPES ; 
 int /*<<< orphan*/  hist ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char const*) ; 
 int sbuf_error (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_voistatdata_hist_tostr (int,TYPE_6__*,int,size_t,int,struct sbuf*,int) ; 
 int /*<<< orphan*/  stats_voistatdata_tdgst_tostr (int,TYPE_6__*,int,size_t,int,struct sbuf*,int) ; 
 int /*<<< orphan*/  tdgst ; 
 int /*<<< orphan*/  voistate ; 

int
stats_voistatdata_tostr(const struct voistatdata *vsd, enum vsd_dtype voi_dtype,
    enum vsd_dtype vsd_dtype, size_t vsd_sz, enum sb_str_fmt fmt,
    struct sbuf *buf, int objdump)
{
	const char *fmtstr;

	if (vsd == NULL || buf == NULL || voi_dtype >= VSD_NUM_DTYPES ||
	    vsd_dtype >= VSD_NUM_DTYPES || fmt >= SB_STRFMT_NUM_FMTS)
		return (EINVAL);

	switch (vsd_dtype) {
	case VSD_DTYPE_VOISTATE:
		switch (fmt) {
		case SB_STRFMT_FREEFORM:
			fmtstr = "prev=";
			break;
		case SB_STRFMT_JSON:
		default:
			fmtstr = "\"prev\":";
			break;
		}
		sbuf_cat(buf, fmtstr);
		/*
		 * Render prev by passing it as *vsd and voi_dtype as vsd_dtype.
		 */
		stats_voistatdata_tostr(
		    (const struct voistatdata *)&CONSTVSD(voistate, vsd)->prev,
		    voi_dtype, voi_dtype, vsd_sz, fmt, buf, objdump);
		break;
	case VSD_DTYPE_INT_S32:
		sbuf_printf(buf, "%d", vsd->int32.s32);
		break;
	case VSD_DTYPE_INT_U32:
		sbuf_printf(buf, "%u", vsd->int32.u32);
		break;
	case VSD_DTYPE_INT_S64:
		sbuf_printf(buf, "%jd", (intmax_t)vsd->int64.s64);
		break;
	case VSD_DTYPE_INT_U64:
		sbuf_printf(buf, "%ju", (uintmax_t)vsd->int64.u64);
		break;
	case VSD_DTYPE_INT_SLONG:
		sbuf_printf(buf, "%ld", vsd->intlong.slong);
		break;
	case VSD_DTYPE_INT_ULONG:
		sbuf_printf(buf, "%lu", vsd->intlong.ulong);
		break;
	case VSD_DTYPE_Q_S32:
		{
		char qstr[Q_MAXSTRLEN(vsd->q32.sq32, 10)];
		Q_TOSTR((s32q_t)vsd->q32.sq32, -1, 10, qstr, sizeof(qstr));
		sbuf_cat(buf, qstr);
		}
		break;
	case VSD_DTYPE_Q_U32:
		{
		char qstr[Q_MAXSTRLEN(vsd->q32.uq32, 10)];
		Q_TOSTR((u32q_t)vsd->q32.uq32, -1, 10, qstr, sizeof(qstr));
		sbuf_cat(buf, qstr);
		}
		break;
	case VSD_DTYPE_Q_S64:
		{
		char qstr[Q_MAXSTRLEN(vsd->q64.sq64, 10)];
		Q_TOSTR((s64q_t)vsd->q64.sq64, -1, 10, qstr, sizeof(qstr));
		sbuf_cat(buf, qstr);
		}
		break;
	case VSD_DTYPE_Q_U64:
		{
		char qstr[Q_MAXSTRLEN(vsd->q64.uq64, 10)];
		Q_TOSTR((u64q_t)vsd->q64.uq64, -1, 10, qstr, sizeof(qstr));
		sbuf_cat(buf, qstr);
		}
		break;
	case VSD_DTYPE_CRHIST32:
	case VSD_DTYPE_DRHIST32:
	case VSD_DTYPE_DVHIST32:
	case VSD_DTYPE_CRHIST64:
	case VSD_DTYPE_DRHIST64:
	case VSD_DTYPE_DVHIST64:
		stats_voistatdata_hist_tostr(voi_dtype, CONSTVSD(hist, vsd),
		    vsd_dtype, vsd_sz, fmt, buf, objdump);
		break;
	case VSD_DTYPE_TDGSTCLUST32:
	case VSD_DTYPE_TDGSTCLUST64:
		stats_voistatdata_tdgst_tostr(voi_dtype,
		    CONSTVSD(tdgst, vsd), vsd_dtype, vsd_sz, fmt, buf,
		    objdump);
		break;
	default:
		break;
	}

	return (sbuf_error(buf));
}