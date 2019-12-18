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
typedef  int uint8_t ;
struct i2c_info {scalar_t__ error; int do_diag; } ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  buf3 ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  SFF_8472_BASE ; 
 int SFF_8472_DDM_DONE ; 
 int SFF_8472_DDM_INTERNAL ; 
 int /*<<< orphan*/  SFF_8472_DIAG_TYPE ; 
 int /*<<< orphan*/  dump_i2c_data (struct i2c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_sfp_connector (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  get_sfp_identifier (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  get_sfp_rx_power (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  get_sfp_temp (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  get_sfp_transceiver_class (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  get_sfp_tx_power (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  get_sfp_voltage (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  print_sfp_vendor (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printf_sfp_transceiver_descr (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  read_i2c (struct i2c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_sfp_status(struct i2c_info *ii, int verbose)
{
	char buf[80], buf2[40], buf3[40];
	uint8_t diag_type, flags;

	/* Read diagnostic monitoring type */
	read_i2c(ii, SFF_8472_BASE, SFF_8472_DIAG_TYPE, 1, (caddr_t)&diag_type);
	if (ii->error != 0)
		return;

	/*
	 * Read monitoring data IFF it is supplied AND is
	 * internally calibrated
	 */
	flags = SFF_8472_DDM_DONE | SFF_8472_DDM_INTERNAL;
	if ((diag_type & flags) == flags)
		ii->do_diag = 1;

	/* Transceiver type */
	get_sfp_identifier(ii, buf, sizeof(buf));
	get_sfp_transceiver_class(ii, buf2, sizeof(buf2));
	get_sfp_connector(ii, buf3, sizeof(buf3));
	if (ii->error == 0)
		printf("\tplugged: %s %s (%s)\n", buf, buf2, buf3);
	print_sfp_vendor(ii, buf, sizeof(buf));
	if (ii->error == 0)
		printf("\t%s\n", buf);

	if (verbose > 5)
		printf_sfp_transceiver_descr(ii, buf, sizeof(buf));
	/*
	 * Request current measurements iff they are provided:
	 */
	if (ii->do_diag != 0) {
		get_sfp_temp(ii, buf, sizeof(buf));
		get_sfp_voltage(ii, buf2, sizeof(buf2));
		printf("\tmodule temperature: %s Voltage: %s\n", buf, buf2);
		get_sfp_rx_power(ii, buf, sizeof(buf));
		get_sfp_tx_power(ii, buf2, sizeof(buf2));
		printf("\tRX: %s TX: %s\n", buf, buf2);
	}

	if (verbose > 2) {
		printf("\n\tSFF8472 DUMP (0xA0 0..127 range):\n");
		dump_i2c_data(ii, SFF_8472_BASE, 0, 128);
	}
}