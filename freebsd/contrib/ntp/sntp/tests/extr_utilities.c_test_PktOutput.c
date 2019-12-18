#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pkt {int /*<<< orphan*/  xmt; int /*<<< orphan*/  li_vn_mode; } ;
struct TYPE_3__ {int l_ui; int l_uf; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePath (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FinishDebugTest (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HTONL_FP (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INPUT_DIR ; 
 int /*<<< orphan*/  InitDebugTest (char*) ; 
 int /*<<< orphan*/  LEAP_NOWARNING ; 
 int /*<<< orphan*/  LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  MODE_SERVER ; 
 int /*<<< orphan*/  NTP_VERSION ; 
 int /*<<< orphan*/  PKT_LI_VN_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pkt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outputFile ; 
 int /*<<< orphan*/  pkt_output (struct pkt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
test_PktOutput(void) {
	char * filename = "debug-output-pkt";
	InitDebugTest(filename);

	struct pkt testpkt;
	memset(&testpkt, 0, sizeof(struct pkt));
	testpkt.li_vn_mode = PKT_LI_VN_MODE(LEAP_NOWARNING,
					    NTP_VERSION,
					    MODE_SERVER);

	l_fp test;
	test.l_ui = 8;
	test.l_uf = 2147483647; // Lots of ones.
	HTONL_FP(&test, &testpkt.xmt);

	pkt_output(&testpkt, LEN_PKT_NOMAC, outputFile);

	FinishDebugTest(CreatePath("debug-input-pkt", INPUT_DIR), filename);
}