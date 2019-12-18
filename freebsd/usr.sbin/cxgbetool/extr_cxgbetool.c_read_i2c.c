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
struct t4_i2c_data {long port_id; long dev_addr; long offset; long len; int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_GET_I2C ; 
 int EINVAL ; 
 long UCHAR_MAX ; 
 int doit (int /*<<< orphan*/ ,struct t4_i2c_data*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 char* str_to_number (char const*,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
read_i2c(int argc, const char *argv[])
{
	char *p;
	long l;
	struct t4_i2c_data i2cd;
	int rc, i;

	if (argc < 3 || argc > 4) {
		warnx("incorrect number of arguments.");
		return (EINVAL);
	}

	p = str_to_number(argv[0], &l, NULL);
	if (*p || l > UCHAR_MAX) {
		warnx("invalid port id \"%s\"", argv[0]);
		return (EINVAL);
	}
	i2cd.port_id = l;

	p = str_to_number(argv[1], &l, NULL);
	if (*p || l > UCHAR_MAX) {
		warnx("invalid i2c device address \"%s\"", argv[1]);
		return (EINVAL);
	}
	i2cd.dev_addr = l;

	p = str_to_number(argv[2], &l, NULL);
	if (*p || l > UCHAR_MAX) {
		warnx("invalid byte offset \"%s\"", argv[2]);
		return (EINVAL);
	}
	i2cd.offset = l;

	if (argc == 4) {
		p = str_to_number(argv[3], &l, NULL);
		if (*p || l > sizeof(i2cd.data)) {
			warnx("invalid number of bytes \"%s\"", argv[3]);
			return (EINVAL);
		}
		i2cd.len = l;
	} else
		i2cd.len = 1;

	rc = doit(CHELSIO_T4_GET_I2C, &i2cd);
	if (rc != 0)
		return (rc);

	for (i = 0; i < i2cd.len; i++)
		printf("0x%x [%u]\n", i2cd.data[i], i2cd.data[i]);

	return (0);
}