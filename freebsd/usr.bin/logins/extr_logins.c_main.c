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
 int a_flag ; 
 int d_flag ; 
 int /*<<< orphan*/  everything ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 void* g_args ; 
 int /*<<< orphan*/  get_groups () ; 
 int /*<<< orphan*/  get_users () ; 
 int getopt (int,char* const*,char*) ; 
 void* l_args ; 
 int /*<<< orphan*/  list_users () ; 
 int m_flag ; 
 int o_flag ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int p_flag ; 
 int s_flag ; 
 int /*<<< orphan*/  select_users () ; 
 int /*<<< orphan*/  sort_users () ; 
 int t_flag ; 
 int u_flag ; 
 int /*<<< orphan*/  usage () ; 
 int x_flag ; 

int
main(int argc, char * const argv[])
{
	int o;

	while ((o = getopt(argc, argv, "adg:l:mopstux")) != -1)
		switch (o) {
		case 'a':
			a_flag = 1;
			break;
		case 'd':
			everything = 0;
			d_flag = 1;
			break;
		case 'g':
			everything = 0;
			g_args = optarg;
			break;
		case 'l':
			everything = 0;
			l_args = optarg;
			break;
		case 'm':
			m_flag = 1;
			break;
		case 'o':
			o_flag = 1;
			break;
		case 'p':
			everything = 0;
			p_flag = 1;
			break;
		case 's':
			everything = 0;
			s_flag = 1;
			break;
		case 't':
			t_flag = 1;
			break;
		case 'u':
			everything = 0;
			u_flag = 1;
			break;
		case 'x':
			x_flag = 1;
			break;
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (argc > 0)
		usage();

	get_groups();
	get_users();
	select_users();
	sort_users();
	list_users();
	exit(0);
}