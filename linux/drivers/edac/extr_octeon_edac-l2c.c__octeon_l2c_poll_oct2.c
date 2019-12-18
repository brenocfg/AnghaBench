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
struct TYPE_4__ {int dbe; int sbe; int type; int syn; int wayidx; } ;
union cvmx_l2c_err_ttgx {void* u64; TYPE_2__ s; } ;
struct TYPE_3__ {int dbe; int sbe; int vdbe; int vsbe; int type; int syn; int wayidx; } ;
union cvmx_l2c_err_tdtx {void* u64; TYPE_1__ s; } ;
struct edac_device_ctl_info {int dummy; } ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_L2C_ERR_TDTX (int) ; 
 int /*<<< orphan*/  CVMX_L2C_ERR_TTGX (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  edac_device_handle_ce (struct edac_device_ctl_info*,int,int,char*) ; 
 int /*<<< orphan*/  edac_device_handle_ue (struct edac_device_ctl_info*,int,int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void _octeon_l2c_poll_oct2(struct edac_device_ctl_info *l2c, int tad)
{
	union cvmx_l2c_err_tdtx err_tdtx, err_tdtx_reset;
	union cvmx_l2c_err_ttgx err_ttgx, err_ttgx_reset;
	char buf1[64];
	char buf2[80];

	err_tdtx_reset.u64 = 0;
	err_tdtx.u64 = cvmx_read_csr(CVMX_L2C_ERR_TDTX(tad));
	if (err_tdtx.s.dbe || err_tdtx.s.sbe ||
	    err_tdtx.s.vdbe || err_tdtx.s.vsbe)
		snprintf(buf1, sizeof(buf1),
			 "type:%d, syn:0x%x, way:%d",
			 err_tdtx.s.type, err_tdtx.s.syn, err_tdtx.s.wayidx);

	if (err_tdtx.s.dbe) {
		snprintf(buf2, sizeof(buf2),
			 "L2D Double bit error (detected):%s", buf1);
		err_tdtx_reset.s.dbe = 1;
		edac_device_handle_ue(l2c, tad, 1, buf2);
	}
	if (err_tdtx.s.sbe) {
		snprintf(buf2, sizeof(buf2),
			 "L2D Single bit error (corrected):%s", buf1);
		err_tdtx_reset.s.sbe = 1;
		edac_device_handle_ce(l2c, tad, 1, buf2);
	}
	if (err_tdtx.s.vdbe) {
		snprintf(buf2, sizeof(buf2),
			 "VBF Double bit error (detected):%s", buf1);
		err_tdtx_reset.s.vdbe = 1;
		edac_device_handle_ue(l2c, tad, 1, buf2);
	}
	if (err_tdtx.s.vsbe) {
		snprintf(buf2, sizeof(buf2),
			 "VBF Single bit error (corrected):%s", buf1);
		err_tdtx_reset.s.vsbe = 1;
		edac_device_handle_ce(l2c, tad, 1, buf2);
	}
	if (err_tdtx_reset.u64)
		cvmx_write_csr(CVMX_L2C_ERR_TDTX(tad), err_tdtx_reset.u64);

	err_ttgx_reset.u64 = 0;
	err_ttgx.u64 = cvmx_read_csr(CVMX_L2C_ERR_TTGX(tad));

	if (err_ttgx.s.dbe || err_ttgx.s.sbe)
		snprintf(buf1, sizeof(buf1),
			 "type:%d, syn:0x%x, way:%d",
			 err_ttgx.s.type, err_ttgx.s.syn, err_ttgx.s.wayidx);

	if (err_ttgx.s.dbe) {
		snprintf(buf2, sizeof(buf2),
			 "Tag Double bit error (detected):%s", buf1);
		err_ttgx_reset.s.dbe = 1;
		edac_device_handle_ue(l2c, tad, 0, buf2);
	}
	if (err_ttgx.s.sbe) {
		snprintf(buf2, sizeof(buf2),
			 "Tag Single bit error (corrected):%s", buf1);
		err_ttgx_reset.s.sbe = 1;
		edac_device_handle_ce(l2c, tad, 0, buf2);
	}
	if (err_ttgx_reset.u64)
		cvmx_write_csr(CVMX_L2C_ERR_TTGX(tad), err_ttgx_reset.u64);
}