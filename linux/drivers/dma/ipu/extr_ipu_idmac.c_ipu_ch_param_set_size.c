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
struct TYPE_4__ {int fw; int fh_l; int fh_h; int sl; int bpp; int pfs; int npb; int sat; int nsb; } ;
struct TYPE_5__ {int bpp; int pfs; int npb; int sat; int ofs0; int ofs1; int ofs2; int ofs3; int wid0; int wid1; int wid2; int wid3; } ;
union chan_param_mem {TYPE_1__ pp; TYPE_2__ ip; } ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  IPU_PIX_FMT_ABGR32 142 
#define  IPU_PIX_FMT_BGR24 141 
#define  IPU_PIX_FMT_BGR32 140 
#define  IPU_PIX_FMT_BGRA32 139 
#define  IPU_PIX_FMT_GENERIC 138 
#define  IPU_PIX_FMT_GENERIC_32 137 
#define  IPU_PIX_FMT_RGB24 136 
#define  IPU_PIX_FMT_RGB32 135 
#define  IPU_PIX_FMT_RGB565 134 
#define  IPU_PIX_FMT_RGBA32 133 
#define  IPU_PIX_FMT_UYVY 132 
#define  IPU_PIX_FMT_YUV420P 131 
#define  IPU_PIX_FMT_YUV420P2 130 
#define  IPU_PIX_FMT_YUV422P 129 
#define  IPU_PIX_FMT_YVU422P 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ipu_ch_param_set_plane_offset (union chan_param_mem*,int,int) ; 
 TYPE_3__ ipu_data ; 

__attribute__((used)) static void ipu_ch_param_set_size(union chan_param_mem *params,
				  uint32_t pixel_fmt, uint16_t width,
				  uint16_t height, uint16_t stride)
{
	u32 u_offset;
	u32 v_offset;

	params->pp.fw		= width - 1;
	params->pp.fh_l		= height - 1;
	params->pp.fh_h		= (height - 1) >> 8;
	params->pp.sl		= stride - 1;

	switch (pixel_fmt) {
	case IPU_PIX_FMT_GENERIC:
		/*Represents 8-bit Generic data */
		params->pp.bpp	= 3;
		params->pp.pfs	= 7;
		params->pp.npb	= 31;
		params->pp.sat	= 2;		/* SAT = use 32-bit access */
		break;
	case IPU_PIX_FMT_GENERIC_32:
		/*Represents 32-bit Generic data */
		params->pp.bpp	= 0;
		params->pp.pfs	= 7;
		params->pp.npb	= 7;
		params->pp.sat	= 2;		/* SAT = use 32-bit access */
		break;
	case IPU_PIX_FMT_RGB565:
		params->ip.bpp	= 2;
		params->ip.pfs	= 4;
		params->ip.npb	= 15;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		params->ip.ofs0	= 0;		/* Red bit offset */
		params->ip.ofs1	= 5;		/* Green bit offset */
		params->ip.ofs2	= 11;		/* Blue bit offset */
		params->ip.ofs3	= 16;		/* Alpha bit offset */
		params->ip.wid0	= 4;		/* Red bit width - 1 */
		params->ip.wid1	= 5;		/* Green bit width - 1 */
		params->ip.wid2	= 4;		/* Blue bit width - 1 */
		break;
	case IPU_PIX_FMT_BGR24:
		params->ip.bpp	= 1;		/* 24 BPP & RGB PFS */
		params->ip.pfs	= 4;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		params->ip.ofs0	= 0;		/* Red bit offset */
		params->ip.ofs1	= 8;		/* Green bit offset */
		params->ip.ofs2	= 16;		/* Blue bit offset */
		params->ip.ofs3	= 24;		/* Alpha bit offset */
		params->ip.wid0	= 7;		/* Red bit width - 1 */
		params->ip.wid1	= 7;		/* Green bit width - 1 */
		params->ip.wid2	= 7;		/* Blue bit width - 1 */
		break;
	case IPU_PIX_FMT_RGB24:
		params->ip.bpp	= 1;		/* 24 BPP & RGB PFS */
		params->ip.pfs	= 4;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		params->ip.ofs0	= 16;		/* Red bit offset */
		params->ip.ofs1	= 8;		/* Green bit offset */
		params->ip.ofs2	= 0;		/* Blue bit offset */
		params->ip.ofs3	= 24;		/* Alpha bit offset */
		params->ip.wid0	= 7;		/* Red bit width - 1 */
		params->ip.wid1	= 7;		/* Green bit width - 1 */
		params->ip.wid2	= 7;		/* Blue bit width - 1 */
		break;
	case IPU_PIX_FMT_BGRA32:
	case IPU_PIX_FMT_BGR32:
	case IPU_PIX_FMT_ABGR32:
		params->ip.bpp	= 0;
		params->ip.pfs	= 4;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		params->ip.ofs0	= 8;		/* Red bit offset */
		params->ip.ofs1	= 16;		/* Green bit offset */
		params->ip.ofs2	= 24;		/* Blue bit offset */
		params->ip.ofs3	= 0;		/* Alpha bit offset */
		params->ip.wid0	= 7;		/* Red bit width - 1 */
		params->ip.wid1	= 7;		/* Green bit width - 1 */
		params->ip.wid2	= 7;		/* Blue bit width - 1 */
		params->ip.wid3	= 7;		/* Alpha bit width - 1 */
		break;
	case IPU_PIX_FMT_RGBA32:
	case IPU_PIX_FMT_RGB32:
		params->ip.bpp	= 0;
		params->ip.pfs	= 4;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		params->ip.ofs0	= 24;		/* Red bit offset */
		params->ip.ofs1	= 16;		/* Green bit offset */
		params->ip.ofs2	= 8;		/* Blue bit offset */
		params->ip.ofs3	= 0;		/* Alpha bit offset */
		params->ip.wid0	= 7;		/* Red bit width - 1 */
		params->ip.wid1	= 7;		/* Green bit width - 1 */
		params->ip.wid2	= 7;		/* Blue bit width - 1 */
		params->ip.wid3	= 7;		/* Alpha bit width - 1 */
		break;
	case IPU_PIX_FMT_UYVY:
		params->ip.bpp	= 2;
		params->ip.pfs	= 6;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		break;
	case IPU_PIX_FMT_YUV420P2:
	case IPU_PIX_FMT_YUV420P:
		params->ip.bpp	= 3;
		params->ip.pfs	= 3;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		u_offset = stride * height;
		v_offset = u_offset + u_offset / 4;
		ipu_ch_param_set_plane_offset(params, u_offset, v_offset);
		break;
	case IPU_PIX_FMT_YVU422P:
		params->ip.bpp	= 3;
		params->ip.pfs	= 2;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		v_offset = stride * height;
		u_offset = v_offset + v_offset / 2;
		ipu_ch_param_set_plane_offset(params, u_offset, v_offset);
		break;
	case IPU_PIX_FMT_YUV422P:
		params->ip.bpp	= 3;
		params->ip.pfs	= 2;
		params->ip.npb	= 7;
		params->ip.sat	= 2;		/* SAT = 32-bit access */
		u_offset = stride * height;
		v_offset = u_offset + u_offset / 2;
		ipu_ch_param_set_plane_offset(params, u_offset, v_offset);
		break;
	default:
		dev_err(ipu_data.dev,
			"mx3 ipu: unimplemented pixel format %d\n", pixel_fmt);
		break;
	}

	params->pp.nsb = 1;
}