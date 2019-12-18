#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARGV_APPEND (char const**,int,char*) ; 
 TYPE_1__ ctx_ ; 
 scalar_t__ exec_command (int,char const**) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
tap_cleanup(int signo)
{
	const char *av[8];
	int ac = 0;

	(void)signo;
#ifdef __FreeBSD__
	ARGV_APPEND(av, ac, "ifconfig");
	ARGV_APPEND(av, ac, ctx_.ifname);
	ARGV_APPEND(av, ac, "destroy");
#else
	ARGV_APPEND(av, ac, "ip");
	ARGV_APPEND(av, ac, "link");
	ARGV_APPEND(av, ac, "del");
	ARGV_APPEND(av, ac, ctx_.ifname);
#endif
	ARGV_APPEND(av, ac, NULL);
	if (exec_command(ac, av)) {
		printf("Failed to destroy tap interface\n");
	}
}