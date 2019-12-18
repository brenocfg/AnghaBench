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
typedef  int uint32_t ;
struct i2c_info {int qsfp; scalar_t__ error; } ;
typedef  int /*<<< orphan*/  buf3 ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  SFF_8436_BASE ; 
 int /*<<< orphan*/  dump_i2c_data (struct i2c_info*,int /*<<< orphan*/ ,int,int) ; 
 int get_qsfp_br (struct i2c_info*) ; 
 int /*<<< orphan*/  get_qsfp_connector (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  get_qsfp_identifier (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  get_qsfp_rev_compliance (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  get_qsfp_rx_power (struct i2c_info*,char*,int,int) ; 
 scalar_t__ get_qsfp_temp (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  get_qsfp_transceiver_class (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  get_qsfp_tx_power (struct i2c_info*,char*,int,int) ; 
 int /*<<< orphan*/  get_qsfp_voltage (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  print_sfp_vendor (struct i2c_info*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_qsfp_status(struct i2c_info *ii, int verbose)
{
	char buf[80], buf2[40], buf3[40];
	uint32_t bitrate;
	int i;

	ii->qsfp = 1;

	/* Transceiver type */
	get_qsfp_identifier(ii, buf, sizeof(buf));
	get_qsfp_transceiver_class(ii, buf2, sizeof(buf2));
	get_qsfp_connector(ii, buf3, sizeof(buf3));
	if (ii->error == 0)
		printf("\tplugged: %s %s (%s)\n", buf, buf2, buf3);
	print_sfp_vendor(ii, buf, sizeof(buf));
	if (ii->error == 0)
		printf("\t%s\n", buf);

	if (verbose > 1) {
		get_qsfp_rev_compliance(ii, buf, sizeof(buf));
		if (ii->error == 0)
			printf("\tcompliance level: %s\n", buf);

		bitrate = get_qsfp_br(ii);
		if (ii->error == 0 && bitrate > 0)
			printf("\tnominal bitrate: %u Mbps\n", bitrate);
	}

	/*
	 * The standards in this area are not clear when the
	 * additional measurements are present or not. Use a valid
	 * temperature reading as an indicator for the presence of
	 * voltage and TX/RX power measurements.
	 */
	if (get_qsfp_temp(ii, buf, sizeof(buf)) == 0) {
		get_qsfp_voltage(ii, buf2, sizeof(buf2));
		printf("\tmodule temperature: %s voltage: %s\n", buf, buf2);
		for (i = 1; i <= 4; i++) {
			get_qsfp_rx_power(ii, buf, sizeof(buf), i);
			get_qsfp_tx_power(ii, buf2, sizeof(buf2), i);
			printf("\tlane %d: RX: %s TX: %s\n", i, buf, buf2);
		}
	}

	if (verbose > 2) {
		printf("\n\tSFF8436 DUMP (0xA0 128..255 range):\n");
		dump_i2c_data(ii, SFF_8436_BASE, 128, 128);
		printf("\n\tSFF8436 DUMP (0xA0 0..81 range):\n");
		dump_i2c_data(ii, SFF_8436_BASE, 0, 82);
	}
}