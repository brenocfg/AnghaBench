#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int l_ui; int l_uf; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePath (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FinishDebugTest (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HTONL_FP (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  INPUT_DIR ; 
 int /*<<< orphan*/  InitDebugTest (char*) ; 
 int /*<<< orphan*/  l_fp_output_dec (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outputFile ; 

void
test_LfpOutputDecimalFormat(void) {
	char * filename = "debug-output-lfp-dec";
	InitDebugTest(filename);

	l_fp test;
	test.l_ui = 6310; // 0x000018A6
	test.l_uf = 308502; // 0x00004B516

	l_fp network;
	HTONL_FP(&test, &network);

	l_fp_output_dec(&network, outputFile);

	FinishDebugTest(CreatePath("debug-input-lfp-dec", INPUT_DIR), filename);
}