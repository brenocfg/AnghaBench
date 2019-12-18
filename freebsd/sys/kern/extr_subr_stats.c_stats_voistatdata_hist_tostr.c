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
typedef  size_t uintmax_t ;
typedef  size_t uint16_t ;
struct voistatdata_numeric {int dummy; } ;
struct voistatdata_hist {int dummy; } ;
struct voistatdata {int dummy; } ;
struct sbuf {int dummy; } ;
typedef  enum vsd_dtype { ____Placeholder_vsd_dtype } vsd_dtype ;
typedef  enum sb_str_fmt { ____Placeholder_sb_str_fmt } sb_str_fmt ;
struct TYPE_2__ {int /*<<< orphan*/  cnt; int /*<<< orphan*/  val; int /*<<< orphan*/  ub; int /*<<< orphan*/  lb; } ;

/* Variables and functions */
 size_t HIST_VSDSZ2NBKTS (int /*<<< orphan*/ ,size_t) ; 
 size_t LIM_MAX ; 
#define  SB_STRFMT_FREEFORM 135 
#define  SB_STRFMT_JSON 134 
 struct voistatdata_numeric* VSD_CONSTCRHIST_FIELDPTR (struct voistatdata_hist const*,int,int /*<<< orphan*/ ) ; 
 struct voistatdata_numeric* VSD_CONSTDRHIST_FIELDPTR (struct voistatdata_hist const*,int,int /*<<< orphan*/ ) ; 
 struct voistatdata_numeric* VSD_CONSTDVHIST_FIELDPTR (struct voistatdata_hist const*,int,int /*<<< orphan*/ ) ; 
 size_t VSD_CONSTHIST_FIELDVAL (struct voistatdata_hist const*,int,int /*<<< orphan*/ ) ; 
#define  VSD_DTYPE_CRHIST32 133 
#define  VSD_DTYPE_CRHIST64 132 
#define  VSD_DTYPE_DRHIST32 131 
#define  VSD_DTYPE_DRHIST64 130 
#define  VSD_DTYPE_DVHIST32 129 
#define  VSD_DTYPE_DVHIST64 128 
 TYPE_1__* bkts ; 
 int /*<<< orphan*/  crhist32 ; 
 int /*<<< orphan*/  crhist64 ; 
 int /*<<< orphan*/  drhist32 ; 
 int /*<<< orphan*/  drhist64 ; 
 int /*<<< orphan*/  dvhist32 ; 
 int /*<<< orphan*/  dvhist64 ; 
 struct voistatdata_numeric** numeric_limits ; 
 int /*<<< orphan*/  oob ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char const*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char) ; 
 int /*<<< orphan*/  stats_voistatdata_tostr (struct voistatdata const*,int,int,int,int,struct sbuf*,int) ; 

__attribute__((used)) static inline void
stats_voistatdata_hist_tostr(enum vsd_dtype voi_dtype,
    const struct voistatdata_hist *hist, enum vsd_dtype hist_dtype,
    size_t hist_dsz, enum sb_str_fmt fmt, struct sbuf *buf, int objdump)
{
	const struct voistatdata_numeric *bkt_lb, *bkt_ub;
	const char *fmtstr;
	int is32bit;
	uint16_t i, nbkts;

	switch (hist_dtype) {
	case VSD_DTYPE_CRHIST32:
		nbkts = HIST_VSDSZ2NBKTS(crhist32, hist_dsz);
		is32bit = 1;
		break;
	case VSD_DTYPE_DRHIST32:
		nbkts = HIST_VSDSZ2NBKTS(drhist32, hist_dsz);
		is32bit = 1;
		break;
	case VSD_DTYPE_DVHIST32:
		nbkts = HIST_VSDSZ2NBKTS(dvhist32, hist_dsz);
		is32bit = 1;
		break;
	case VSD_DTYPE_CRHIST64:
		nbkts = HIST_VSDSZ2NBKTS(crhist64, hist_dsz);
		is32bit = 0;
		break;
	case VSD_DTYPE_DRHIST64:
		nbkts = HIST_VSDSZ2NBKTS(drhist64, hist_dsz);
		is32bit = 0;
		break;
	case VSD_DTYPE_DVHIST64:
		nbkts = HIST_VSDSZ2NBKTS(dvhist64, hist_dsz);
		is32bit = 0;
		break;
	default:
		return;
	}

	switch (fmt) {
	case SB_STRFMT_FREEFORM:
		fmtstr = "nbkts=%hu, ";
		break;
	case SB_STRFMT_JSON:
	default:
		fmtstr = "\"nbkts\":%hu,";
		break;
	}
	sbuf_printf(buf, fmtstr, nbkts);

	switch (fmt) {
		case SB_STRFMT_FREEFORM:
			fmtstr = (is32bit ? "oob=%u" : "oob=%ju");
			break;
		case SB_STRFMT_JSON:
		default:
			fmtstr = (is32bit ? "\"oob\":%u,\"bkts\":[" :
			    "\"oob\":%ju,\"bkts\":[");
			break;
	}
	sbuf_printf(buf, fmtstr, is32bit ? VSD_CONSTHIST_FIELDVAL(hist,
	    hist_dtype, oob) : (uintmax_t)VSD_CONSTHIST_FIELDVAL(hist,
	    hist_dtype, oob));

	for (i = 0; i < nbkts; i++) {
		switch (hist_dtype) {
		case VSD_DTYPE_CRHIST32:
		case VSD_DTYPE_CRHIST64:
			bkt_lb = VSD_CONSTCRHIST_FIELDPTR(hist, hist_dtype,
			    bkts[i].lb);
			if (i < nbkts - 1)
				bkt_ub = VSD_CONSTCRHIST_FIELDPTR(hist,
				    hist_dtype, bkts[i + 1].lb);
			else
				bkt_ub = &numeric_limits[LIM_MAX][voi_dtype];
			break;
		case VSD_DTYPE_DRHIST32:
		case VSD_DTYPE_DRHIST64:
			bkt_lb = VSD_CONSTDRHIST_FIELDPTR(hist, hist_dtype,
			    bkts[i].lb);
			bkt_ub = VSD_CONSTDRHIST_FIELDPTR(hist, hist_dtype,
			    bkts[i].ub);
			break;
		case VSD_DTYPE_DVHIST32:
		case VSD_DTYPE_DVHIST64:
			bkt_lb = bkt_ub = VSD_CONSTDVHIST_FIELDPTR(hist,
			    hist_dtype, bkts[i].val);
			break;
		default:
			break;
		}

		switch (fmt) {
		case SB_STRFMT_FREEFORM:
			fmtstr = "\n\t\t\t\t";
			break;
		case SB_STRFMT_JSON:
		default:
			fmtstr = "{";
			break;
		}
		sbuf_cat(buf, fmtstr);

		if (objdump) {
			switch (fmt) {
			case SB_STRFMT_FREEFORM:
				fmtstr = "bkt[%hu].";
				break;
			case SB_STRFMT_JSON:
			default:
				fmtstr = "\"bkt\":%hu,";
				break;
			}
			sbuf_printf(buf, fmtstr, i);
		}

		switch (fmt) {
		case SB_STRFMT_FREEFORM:
			fmtstr = "{lb=";
			break;
		case SB_STRFMT_JSON:
		default:
			fmtstr = "\"lb\":";
			break;
		}
		sbuf_cat(buf, fmtstr);
		stats_voistatdata_tostr((const struct voistatdata *)bkt_lb,
		    voi_dtype, voi_dtype, sizeof(struct voistatdata_numeric),
		    fmt, buf, objdump);

		switch (fmt) {
		case SB_STRFMT_FREEFORM:
			fmtstr = ",ub=";
			break;
		case SB_STRFMT_JSON:
		default:
			fmtstr = ",\"ub\":";
			break;
		}
		sbuf_cat(buf, fmtstr);
		stats_voistatdata_tostr((const struct voistatdata *)bkt_ub,
		    voi_dtype, voi_dtype, sizeof(struct voistatdata_numeric),
		    fmt, buf, objdump);

		switch (fmt) {
		case SB_STRFMT_FREEFORM:
			fmtstr = is32bit ? ",cnt=%u}" : ",cnt=%ju}";
			break;
		case SB_STRFMT_JSON:
		default:
			fmtstr = is32bit ? ",\"cnt\":%u}" : ",\"cnt\":%ju}";
			break;
		}
		sbuf_printf(buf, fmtstr, is32bit ?
		    VSD_CONSTHIST_FIELDVAL(hist, hist_dtype, bkts[i].cnt) :
		    (uintmax_t)VSD_CONSTHIST_FIELDVAL(hist, hist_dtype,
		    bkts[i].cnt));

		if (fmt == SB_STRFMT_JSON && i < nbkts - 1)
			sbuf_putc(buf, ',');
	}
	if (fmt == SB_STRFMT_JSON)
		sbuf_cat(buf, "]");
}