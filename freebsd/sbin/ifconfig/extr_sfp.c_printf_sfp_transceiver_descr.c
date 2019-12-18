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
struct i2c_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFF_8472_BASE ; 
 int /*<<< orphan*/  SFF_8472_TRANS_START ; 
 int /*<<< orphan*/  cab_tech ; 
 int /*<<< orphan*/  eth_10g ; 
 int /*<<< orphan*/  eth_compat ; 
 int /*<<< orphan*/  fc_len ; 
 int /*<<< orphan*/  fc_media ; 
 int /*<<< orphan*/  fc_speed ; 
 char* find_zero_bit (int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  read_i2c (struct i2c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void
printf_sfp_transceiver_descr(struct i2c_info *ii, char *buf, size_t size)
{
	char xbuf[12];
	const char *tech_class, *tech_len, *tech_tech, *tech_media, *tech_speed;

	tech_class = NULL;
	tech_len = NULL;
	tech_tech = NULL;
	tech_media = NULL;
	tech_speed = NULL;

	/* Read bytes 3-10 at once */
	read_i2c(ii, SFF_8472_BASE, SFF_8472_TRANS_START, 8, &xbuf[3]);

	/* Check 10G ethernet first */
	tech_class = find_zero_bit(eth_10g, xbuf[3], 1);
	if (tech_class == NULL) {
		/* No match. Try 1G */
		tech_class = find_zero_bit(eth_compat, xbuf[6], 1);
	}

	tech_len = find_zero_bit(fc_len, xbuf[7], 1);
	tech_tech = find_zero_bit(cab_tech, xbuf[7] << 8 | xbuf[8], 2);
	tech_media = find_zero_bit(fc_media, xbuf[9], 1);
	tech_speed = find_zero_bit(fc_speed, xbuf[10], 1);

	printf("Class: %s\n", tech_class);
	printf("Length: %s\n", tech_len);
	printf("Tech: %s\n", tech_tech);
	printf("Media: %s\n", tech_media);
	printf("Speed: %s\n", tech_speed);
}