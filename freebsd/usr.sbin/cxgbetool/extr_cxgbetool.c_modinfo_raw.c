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
struct t4_i2c_data {int port_id; int dev_addr; int offset; int len; int* data; } ;
typedef  int /*<<< orphan*/  i2cd ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_GET_I2C ; 
 int /*<<< orphan*/  bzero (struct t4_i2c_data*,int) ; 
 int doit (int /*<<< orphan*/ ,struct t4_i2c_data*) ; 
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  printf (char*,char,char,char,char,char,char,char,char,...) ; 

__attribute__((used)) static int
modinfo_raw(int port_id)
{
	uint8_t offset;
	struct t4_i2c_data i2cd;
	int rc;

	for (offset = 0; offset < 96; offset += sizeof(i2cd.data)) {
		bzero(&i2cd, sizeof(i2cd));
		i2cd.port_id = port_id;
		i2cd.dev_addr = 0xa0;
		i2cd.offset = offset;
		i2cd.len = sizeof(i2cd.data);
		rc = doit(CHELSIO_T4_GET_I2C, &i2cd);
		if (rc != 0)
			return (rc);
		printf("%02x:  %02x %02x %02x %02x  %02x %02x %02x %02x",
		    offset, i2cd.data[0], i2cd.data[1], i2cd.data[2],
		    i2cd.data[3], i2cd.data[4], i2cd.data[5], i2cd.data[6],
		    i2cd.data[7]);

		printf("  %c%c%c%c %c%c%c%c\n",
		    isprint(i2cd.data[0]) ? i2cd.data[0] : '.',
		    isprint(i2cd.data[1]) ? i2cd.data[1] : '.',
		    isprint(i2cd.data[2]) ? i2cd.data[2] : '.',
		    isprint(i2cd.data[3]) ? i2cd.data[3] : '.',
		    isprint(i2cd.data[4]) ? i2cd.data[4] : '.',
		    isprint(i2cd.data[5]) ? i2cd.data[5] : '.',
		    isprint(i2cd.data[6]) ? i2cd.data[6] : '.',
		    isprint(i2cd.data[7]) ? i2cd.data[7] : '.');
	}

	return (0);
}