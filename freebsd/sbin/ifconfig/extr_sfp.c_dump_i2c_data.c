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
struct i2c_info {scalar_t__ error; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_i2c (struct i2c_info*,scalar_t__,scalar_t__,int,unsigned char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
dump_i2c_data(struct i2c_info *ii, uint8_t addr, uint8_t off, uint8_t len)
{
	unsigned char buf[16];
	int i, read;

	while (len > 0) {
		memset(buf, 0, sizeof(buf));
		read = MIN(sizeof(buf), len);
		read_i2c(ii, addr, off, read, buf);
		if (ii->error != 0) {
			fprintf(stderr, "Error reading i2c info\n");
			return;
		}

		printf("\t");
		for (i = 0; i < read; i++)
			printf("%02X ", buf[i]);
		printf("\n");
		len -= read;
		off += read;
	}
}