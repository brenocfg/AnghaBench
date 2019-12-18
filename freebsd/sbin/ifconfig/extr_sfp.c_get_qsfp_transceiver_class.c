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
struct i2c_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFF_8436_BASE ; 
 int /*<<< orphan*/  SFF_8436_CODE_E1040100G ; 
 int /*<<< orphan*/  SFF_8436_OPTIONS_START ; 
 int SFF_8636_EXT_COMPLIANCE ; 
 int /*<<< orphan*/  eth_1040g ; 
 int /*<<< orphan*/  eth_extended_comp ; 
 char* find_value (int /*<<< orphan*/ ,int) ; 
 char* find_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  read_i2c (struct i2c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static void
get_qsfp_transceiver_class(struct i2c_info *ii, char *buf, size_t size)
{
	const char *tech_class;
	uint8_t code;

	read_i2c(ii, SFF_8436_BASE, SFF_8436_CODE_E1040100G, 1, &code);

	/* Check for extended specification compliance */
	if (code & SFF_8636_EXT_COMPLIANCE) {
		read_i2c(ii, SFF_8436_BASE, SFF_8436_OPTIONS_START, 1, &code);
		tech_class = find_value(eth_extended_comp, code);
	} else
		/* Check 10/40G Ethernet class only */
		tech_class = find_zero_bit(eth_1040g, code, 1);

	if (tech_class == NULL)
		tech_class = "Unknown";

	snprintf(buf, size, "%s", tech_class);
}