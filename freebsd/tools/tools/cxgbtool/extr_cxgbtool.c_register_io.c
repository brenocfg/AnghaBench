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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int read_reg (char const*,int) ; 
 int strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 
 int /*<<< orphan*/  write_reg (char const*,int,int) ; 

__attribute__((used)) static int
register_io(int argc, char *argv[], int start_arg,
		       const char *iff_name)
{
	char *p;
	uint32_t addr, val = 0, w = 0;

	if (argc != start_arg + 1) return -1;

	addr = strtoul(argv[start_arg], &p, 0);
	if (p == argv[start_arg]) return -1;
	if (*p == '=' && p[1]) {
		val = strtoul(p + 1, &p, 0);
		w = 1;
	}
	if (*p) {
		warnx("bad parameter \"%s\"", argv[start_arg]);
		return -1;
	}

	if (w)
		write_reg(iff_name, addr, val);
	else {
		val = read_reg(iff_name, addr);
		printf("%#x [%u]\n", val, val);
	}
	return 0;
}