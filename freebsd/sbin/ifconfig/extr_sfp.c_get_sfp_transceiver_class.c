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
typedef  scalar_t__ uint8_t ;
struct i2c_info {int dummy; } ;
typedef  scalar_t__* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SFF_8472_BASE ; 
 scalar_t__ SFF_8472_TRANS ; 
 scalar_t__ SFF_8472_TRANS_START ; 
 int /*<<< orphan*/  eth_10g ; 
 int /*<<< orphan*/  eth_compat ; 
 int /*<<< orphan*/  eth_extended_comp ; 
 char* find_value (int /*<<< orphan*/ ,scalar_t__) ; 
 char* find_zero_bit (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  read_i2c (struct i2c_info*,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static void
get_sfp_transceiver_class(struct i2c_info *ii, char *buf, size_t size)
{
	const char *tech_class;
	uint8_t code;

	/* Use extended compliance code if it's valid */
	read_i2c(ii, SFF_8472_BASE, SFF_8472_TRANS, 1, &code);
	if (code != 0)
		tech_class = find_value(eth_extended_comp, code);
	else {
		/* Next, check 10G Ethernet/IB CCs */
		read_i2c(ii, SFF_8472_BASE, SFF_8472_TRANS_START, 1, &code);
		tech_class = find_zero_bit(eth_10g, code, 1);
		if (tech_class == NULL) {
			/* No match. Try Ethernet 1G */
			read_i2c(ii, SFF_8472_BASE, SFF_8472_TRANS_START + 3,
			    1, (caddr_t)&code);
			tech_class = find_zero_bit(eth_compat, code, 1);
		}
	}

	if (tech_class == NULL)
		tech_class = "Unknown";

	snprintf(buf, size, "%s", tech_class);
}