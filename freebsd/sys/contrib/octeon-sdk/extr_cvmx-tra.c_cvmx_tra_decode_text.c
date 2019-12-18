#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int type; int source; int timestamp; int /*<<< orphan*/  discontinuity; scalar_t__ addresslo; scalar_t__ addresshi; } ;
struct TYPE_15__ {scalar_t__ data; scalar_t__ datahi; } ;
struct TYPE_20__ {int source; int timestamp; size_t dest; scalar_t__ addresslo; scalar_t__ addresshi; scalar_t__ mask; int /*<<< orphan*/  discontinuity; } ;
struct TYPE_19__ {int source; size_t dest; scalar_t__ addresslo; scalar_t__ addresshi; scalar_t__ subid; } ;
struct TYPE_18__ {int source; scalar_t__ addresslo; scalar_t__ addresshi; scalar_t__ mask; } ;
struct TYPE_24__ {int type; int timestamp; size_t source; int /*<<< orphan*/  discontinuity; scalar_t__ address; } ;
struct TYPE_26__ {size_t source; size_t dest; scalar_t__ address; scalar_t__ mask; } ;
struct TYPE_23__ {size_t source; size_t dest; scalar_t__ address; scalar_t__ subid; } ;
struct TYPE_22__ {size_t source; scalar_t__ address; scalar_t__ mask; } ;
struct TYPE_16__ {TYPE_4__ cmn2; TYPE_10__ u128; TYPE_3__ iob2; TYPE_2__ iobld2; TYPE_1__ store2; TYPE_7__ cmn; TYPE_9__ iob; TYPE_6__ iobld; TYPE_5__ store; } ;
typedef  TYPE_11__ cvmx_tra_data_t ;
struct TYPE_25__ {int time_grn; } ;
struct TYPE_17__ {TYPE_8__ s; } ;
typedef  TYPE_12__ cvmx_tra_ctl_t ;

/* Variables and functions */
#define  CVMX_TRA_FILT_CLR16 178 
#define  CVMX_TRA_FILT_CLR32 177 
#define  CVMX_TRA_FILT_CLR64 176 
#define  CVMX_TRA_FILT_CLR8 175 
#define  CVMX_TRA_FILT_DECR16 174 
#define  CVMX_TRA_FILT_DECR32 173 
#define  CVMX_TRA_FILT_DECR64 172 
#define  CVMX_TRA_FILT_DECR8 171 
#define  CVMX_TRA_FILT_DWB 170 
#define  CVMX_TRA_FILT_FAA32 169 
#define  CVMX_TRA_FILT_FAA64 168 
#define  CVMX_TRA_FILT_FAS32 167 
#define  CVMX_TRA_FILT_FAS64 166 
#define  CVMX_TRA_FILT_INCR16 165 
#define  CVMX_TRA_FILT_INCR32 164 
#define  CVMX_TRA_FILT_INCR64 163 
#define  CVMX_TRA_FILT_INCR8 162 
#define  CVMX_TRA_FILT_INVL2 161 
#define  CVMX_TRA_FILT_IOBDMA 160 
#define  CVMX_TRA_FILT_IOBLD16 159 
#define  CVMX_TRA_FILT_IOBLD32 158 
#define  CVMX_TRA_FILT_IOBLD64 157 
#define  CVMX_TRA_FILT_IOBLD8 156 
#define  CVMX_TRA_FILT_IOBST16 155 
#define  CVMX_TRA_FILT_IOBST32 154 
#define  CVMX_TRA_FILT_IOBST64 153 
#define  CVMX_TRA_FILT_IOBST8 152 
#define  CVMX_TRA_FILT_LCKL2 151 
#define  CVMX_TRA_FILT_LDD 150 
#define  CVMX_TRA_FILT_LDI 149 
#define  CVMX_TRA_FILT_LDT 148 
#define  CVMX_TRA_FILT_LTGL2I 147 
#define  CVMX_TRA_FILT_PL2 146 
#define  CVMX_TRA_FILT_PSL1 145 
#define  CVMX_TRA_FILT_RPL2 144 
#define  CVMX_TRA_FILT_SAA32 143 
#define  CVMX_TRA_FILT_SAA64 142 
#define  CVMX_TRA_FILT_SET16 141 
#define  CVMX_TRA_FILT_SET32 140 
#define  CVMX_TRA_FILT_SET64 139 
#define  CVMX_TRA_FILT_SET8 138 
#define  CVMX_TRA_FILT_STC 137 
#define  CVMX_TRA_FILT_STF 136 
#define  CVMX_TRA_FILT_STFIL1 135 
#define  CVMX_TRA_FILT_STGL2I 134 
#define  CVMX_TRA_FILT_STP 133 
#define  CVMX_TRA_FILT_STT 132 
#define  CVMX_TRA_FILT_STTIL1 131 
#define  CVMX_TRA_FILT_WBIL2 130 
#define  CVMX_TRA_FILT_WBIL2I 129 
#define  CVMX_TRA_FILT_WBL2 128 
 int /*<<< orphan*/ * DEST_ARRAY ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 int /*<<< orphan*/  OCTEON_CN5XXX ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SOURCE_ARRAY ; 
 int /*<<< orphan*/ * TYPE_ARRAY ; 
 int /*<<< orphan*/ * TYPE_ARRAY2 ; 
 int /*<<< orphan*/  _cvmx_tra_unit ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,unsigned long long,unsigned long long,char,...) ; 

void cvmx_tra_decode_text(cvmx_tra_ctl_t tra_ctl, cvmx_tra_data_t data)
{
    if (OCTEON_IS_MODEL(OCTEON_CN3XXX) || OCTEON_IS_MODEL(OCTEON_CN5XXX))
    {
        /* The type is a five bit field for some entries and 4 for other. The four
           bit entries can be mis-typed if the top is set */
        int type = data.cmn.type;

        if (type >= 0x1a)
            type &= 0xf;

        switch (type)
        {
            case 0:  /* DWB */
            case 1:  /* PL2 */
            case 2:  /* PSL1 */
            case 3:  /* LDD */
            case 4:  /* LDI */
            case 5:  /* LDT */
                cvmx_dprintf("0x%016llx %c%+10d %s %s 0x%016llx\n",
                    (unsigned long long)data.u128.data,
                    (data.cmn.discontinuity) ? 'D' : ' ',
                    data.cmn.timestamp << (tra_ctl.s.time_grn*3),
                    TYPE_ARRAY[type],
                    SOURCE_ARRAY[data.cmn.source],
                    (unsigned long long)data.cmn.address);
                break;
            case 6:  /* STF */
            case 7:  /* STC */
            case 8:  /* STP */
            case 9:  /* STT */
            case 16: /* SAA */
                cvmx_dprintf("0x%016llx %c%+10d %s %s mask=0x%02x 0x%016llx\n",
                   (unsigned long long)data.u128.data,
                   (data.cmn.discontinuity) ? 'D' : ' ',
                   data.cmn.timestamp << (tra_ctl.s.time_grn*3),
                   TYPE_ARRAY[type],
                   SOURCE_ARRAY[data.store.source],
                   (unsigned int)data.store.mask,
                   (unsigned long long)data.store.address << 3);
                break;
            case 10:  /* IOBLD8 */
            case 11:  /* IOBLD16 */
            case 12:  /* IOBLD32 */
            case 13:  /* IOBLD64 */
            case 14:  /* IOBST */
                cvmx_dprintf("0x%016llx %c%+10d %s %s->%s subdid=0x%x 0x%016llx\n",
                   (unsigned long long)data.u128.data,
                   (data.cmn.discontinuity) ? 'D' : ' ',
                   data.cmn.timestamp << (tra_ctl.s.time_grn*3),
                   TYPE_ARRAY[type],
                   SOURCE_ARRAY[data.iobld.source],
                   DEST_ARRAY[data.iobld.dest],
                   (unsigned int)data.iobld.subid,
                   (unsigned long long)data.iobld.address);
                break;
            case 15:  /* IOBDMA */
                cvmx_dprintf("0x%016llx %c%+10d %s %s->%s len=0x%x 0x%016llx\n",
                   (unsigned long long)data.u128.data,
                   (data.cmn.discontinuity) ? 'D' : ' ',
                   data.cmn.timestamp << (tra_ctl.s.time_grn*3),
                   TYPE_ARRAY[type],
                   SOURCE_ARRAY[data.iob.source],
                   DEST_ARRAY[data.iob.dest],
                   (unsigned int)data.iob.mask,
                   (unsigned long long)data.iob.address << 3);
                break;
            default:
                cvmx_dprintf("0x%016llx %c%+10d Unknown format\n",
                   (unsigned long long)data.u128.data,
                   (data.cmn.discontinuity) ? 'D' : ' ',
                   data.cmn.timestamp << (tra_ctl.s.time_grn*3));
                break;
        }
    }
    else
    {
        int type;
        int srcId;

        type = data.cmn2.type;

        switch (1ull<<type)
        {
            case CVMX_TRA_FILT_DECR64:
            case CVMX_TRA_FILT_DECR32:
            case CVMX_TRA_FILT_DECR16:
            case CVMX_TRA_FILT_DECR8:
            case CVMX_TRA_FILT_INCR64:
            case CVMX_TRA_FILT_INCR32:
            case CVMX_TRA_FILT_INCR16:
            case CVMX_TRA_FILT_INCR8:
            case CVMX_TRA_FILT_CLR64:
            case CVMX_TRA_FILT_CLR32:
            case CVMX_TRA_FILT_CLR16:
            case CVMX_TRA_FILT_CLR8:
            case CVMX_TRA_FILT_SET64:
            case CVMX_TRA_FILT_SET32:
            case CVMX_TRA_FILT_SET16:
            case CVMX_TRA_FILT_SET8:
            case CVMX_TRA_FILT_LCKL2:
            case CVMX_TRA_FILT_WBIL2:
            case CVMX_TRA_FILT_INVL2:
            case CVMX_TRA_FILT_STGL2I:
            case CVMX_TRA_FILT_LTGL2I:
            case CVMX_TRA_FILT_WBIL2I:
            case CVMX_TRA_FILT_WBL2:
            case CVMX_TRA_FILT_DWB:
            case CVMX_TRA_FILT_RPL2:
            case CVMX_TRA_FILT_PL2:
            case CVMX_TRA_FILT_LDI:
            case CVMX_TRA_FILT_LDT:
                /* CN68XX has 32 cores which are distributed to use different
                   trace buffers, decode the core that has data */
                if (OCTEON_IS_MODEL(OCTEON_CN68XX))
                {
                    if (data.cmn2.source <= 7)
                    {
                        srcId = _cvmx_tra_unit + (data.cmn2.source * 4);
                        if (srcId >= 16)
                            srcId += 16;
                    }
                    else
                        srcId = (data.cmn2.source);
                }
                else
                        srcId = (data.cmn2.source);
                
                cvmx_dprintf("0x%016llx%016llx %c%+10d %s %s 0x%016llx%llx\n",
                   (unsigned long long)data.u128.datahi, (unsigned long long)data.u128.data,
                   (data.cmn2.discontinuity) ? 'D' : ' ',
                   data.cmn2.timestamp << (tra_ctl.s.time_grn*3),
                   TYPE_ARRAY2[type],
                   SOURCE_ARRAY[srcId],
                   (unsigned long long)data.cmn2.addresshi,
                   (unsigned long long)data.cmn2.addresslo);
                break;
            case CVMX_TRA_FILT_PSL1:
            case CVMX_TRA_FILT_LDD:
            case CVMX_TRA_FILT_FAS64:
            case CVMX_TRA_FILT_FAS32:
            case CVMX_TRA_FILT_FAA64:
            case CVMX_TRA_FILT_FAA32:
            case CVMX_TRA_FILT_SAA64:
            case CVMX_TRA_FILT_SAA32:
            case CVMX_TRA_FILT_STC:
            case CVMX_TRA_FILT_STF:
            case CVMX_TRA_FILT_STP:
            case CVMX_TRA_FILT_STT:
            case CVMX_TRA_FILT_STTIL1:
            case CVMX_TRA_FILT_STFIL1:
                /* CN68XX has 32 cores which are distributed to use different
                   trace buffers, decode the core that has data */
                if (OCTEON_IS_MODEL(OCTEON_CN68XX))
                {
                    if (data.store2.source <= 7)
                    {
                        srcId = _cvmx_tra_unit + (data.store2.source * 4);
                        if (srcId >= 16)
                            srcId += 16;
                    }
                    else
                        srcId = data.store2.source;
                }
                else
                        srcId = data.store2.source;

                cvmx_dprintf("0x%016llx%016llx %c%+10d %s %s mask=0x%02x 0x%016llx%llx\n",
                   (unsigned long long)data.u128.datahi, (unsigned long long)data.u128.data,
                   (data.cmn2.discontinuity) ? 'D' : ' ',
                   data.cmn2.timestamp << (tra_ctl.s.time_grn*3),
                   TYPE_ARRAY2[type],
                   SOURCE_ARRAY[srcId],
                   (unsigned int)data.store2.mask,
                   (unsigned long long)data.store2.addresshi,
                   (unsigned long long)data.store2.addresslo);
                break;
            case CVMX_TRA_FILT_IOBST64:
            case CVMX_TRA_FILT_IOBST32:
            case CVMX_TRA_FILT_IOBST16:
            case CVMX_TRA_FILT_IOBST8:
            case CVMX_TRA_FILT_IOBLD64:
            case CVMX_TRA_FILT_IOBLD32:
            case CVMX_TRA_FILT_IOBLD16:
            case CVMX_TRA_FILT_IOBLD8:
                /* CN68XX has 32 cores which are distributed to use different
                   trace buffers, decode the core that has data */
                if (OCTEON_IS_MODEL(OCTEON_CN68XX))
                {
                    if (data.iobld2.source <= 7)
                    {
                        srcId = _cvmx_tra_unit + (data.iobld2.source * 4);
                        if (srcId >= 16)
                            srcId += 16;
                    }
                    else
                        srcId = data.iobld2.source;
                }
                else
                        srcId = data.iobld2.source;

                cvmx_dprintf("0x%016llx%016llx %c%+10d %s %s->%s subdid=0x%x 0x%016llx%llx\n",
                   (unsigned long long)data.u128.datahi, (unsigned long long)data.u128.data,
                   (data.cmn2.discontinuity) ? 'D' : ' ',
                   data.cmn2.timestamp << (tra_ctl.s.time_grn*3),
                   TYPE_ARRAY2[type],
                   SOURCE_ARRAY[srcId],
                   DEST_ARRAY[data.iobld2.dest],
                   (unsigned int)data.iobld2.subid,
                   (unsigned long long)data.iobld2.addresshi,
                   (unsigned long long)data.iobld2.addresslo);
                break;
            case CVMX_TRA_FILT_IOBDMA:
                /* CN68XX has 32 cores which are distributed to use different
                   trace buffers, decode the core that has data */
                if (OCTEON_IS_MODEL(OCTEON_CN68XX))
                {
                    if (data.iob2.source <= 7)
                    {
                        srcId = _cvmx_tra_unit + (data.iob2.source * 4);
                        if (srcId >= 16)
                            srcId += 16;
                    }
                    else
                        srcId = data.iob2.source;
                }
                else
                        srcId = data.iob2.source;

                cvmx_dprintf("0x%016llx%016llx %c%+10d %s %s->%s len=0x%x 0x%016llx%llx\n",
                   (unsigned long long)data.u128.datahi, (unsigned long long)data.u128.data,
                   (data.iob2.discontinuity) ? 'D' : ' ',
                   data.iob2.timestamp << (tra_ctl.s.time_grn*3),
                   TYPE_ARRAY2[type],
                   SOURCE_ARRAY[srcId],
                   DEST_ARRAY[data.iob2.dest],
                   (unsigned int)data.iob2.mask,
                   (unsigned long long)data.iob2.addresshi << 3,
                   (unsigned long long)data.iob2.addresslo << 3);
                break;
            default:
                cvmx_dprintf("0x%016llx%016llx %c%+10d Unknown format\n",
                   (unsigned long long)data.u128.datahi, (unsigned long long)data.u128.data,
                   (data.cmn2.discontinuity) ? 'D' : ' ',
                   data.cmn2.timestamp << (tra_ctl.s.time_grn*3));
                break;
        }
    }
}