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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  printf (char*,long long,long long) ; 
 int read_reg (long,int,long long*) ; 
 char* str_to_number (char const*,long*,long long*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 int write_reg (long,int,long long) ; 

__attribute__((used)) static int
register_io(int argc, const char *argv[], int size)
{
	char *p, *v;
	long addr;
	long long val;
	int w = 0, rc;

	if (argc == 1) {
		/* <reg> OR <reg>=<value> */

		p = str_to_number(argv[0], &addr, NULL);
		if (*p) {
			if (*p != '=') {
				warnx("invalid register \"%s\"", argv[0]);
				return (EINVAL);
			}

			w = 1;
			v = p + 1;
			p = str_to_number(v, NULL, &val);

			if (*p) {
				warnx("invalid value \"%s\"", v);
				return (EINVAL);
			}
		}

	} else if (argc == 2) {
		/* <reg> <value> */

		w = 1;

		p = str_to_number(argv[0], &addr, NULL);
		if (*p) {
			warnx("invalid register \"%s\"", argv[0]);
			return (EINVAL);
		}

		p = str_to_number(argv[1], NULL, &val);
		if (*p) {
			warnx("invalid value \"%s\"", argv[1]);
			return (EINVAL);
		}
	} else {
		warnx("reg: invalid number of arguments (%d)", argc);
		return (EINVAL);
	}

	if (w)
		rc = write_reg(addr, size, val);
	else {
		rc = read_reg(addr, size, &val);
		if (rc == 0)
			printf("0x%llx [%llu]\n", val, val);
	}

	return (rc);
}