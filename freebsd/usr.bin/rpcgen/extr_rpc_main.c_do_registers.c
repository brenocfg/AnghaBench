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
 int /*<<< orphan*/  check_nettype (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ inetdflag ; 
 scalar_t__ streq (char const*,char*) ; 
 int /*<<< orphan*/  tirpcflag ; 
 int /*<<< orphan*/  valid_i_nettypes ; 
 int /*<<< orphan*/  valid_ti_nettypes ; 
 int /*<<< orphan*/  write_inetd_register (char const*) ; 
 int /*<<< orphan*/  write_netid_register (char const*) ; 
 int /*<<< orphan*/  write_nettype_register (char const*) ; 

__attribute__((used)) static int
do_registers(int argc, const char *argv[])
{
	int i;

	if (inetdflag || !tirpcflag) {
		for (i = 1; i < argc; i++) {
			if (streq(argv[i], "-s")) {
				if (!check_nettype(argv[i + 1],
						    valid_i_nettypes))
					return (0);
				write_inetd_register(argv[i + 1]);
				i++;
			}
		}
	} else {
		for (i = 1; i < argc; i++)
			if (streq(argv[i], "-s")) {
				if (!check_nettype(argv[i + 1],
						    valid_ti_nettypes))
					return (0);
				write_nettype_register(argv[i + 1]);
				i++;
			} else if (streq(argv[i], "-n")) {
				write_netid_register(argv[i + 1]);
				i++;
			}
	}
	return (1);
}