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
typedef  int /*<<< orphan*/  u32 ;
struct sa_open_data {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ipv4_list_add_net (struct sa_open_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_list_add_netmask (struct sa_open_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_list_add_range (struct sa_open_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv4_stohl (char*) ; 
 int /*<<< orphan*/  is_ipv4_addr (char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int salist_cmd_parse(struct sa_open_data *od, char *cmd, gfp_t gfp)
{
	char *a1 = NULL, *a2 = NULL;
	char *sep;
	char sc;
	int n = 32;

	/* Case 3: Append an item */
	
	/* Check IP description part: network segment or range? */
	if ((sep = strchr(cmd, '/'))) { }
	else if ((sep = strchr(cmd, '-'))) { }
	else if ((sep = strchr(cmd, ':'))) { }
	
	if (sep) {
		/* Describes a subnet or range. */
		sc = *sep;
		*sep = '\0';

		a1 = cmd;
		a2 = sep + 1;

		if (*a2 == '\0') {
			fprintf(stderr, "Nothing after '%c'.\n", sc);
			return -EINVAL;
		}
	} else {
		/* Describes a single IP. */
		sc = '\0';
		a1 = cmd;
	}
	
	switch (sc) {
	case '/':
		/* 10.10.20.0/24 */
		/* ------------------------------------ */
		if (is_ipv4_addr(a2)) {
			ipv4_list_add_netmask(od, ipv4_stohl(a1), ipv4_stohl(a2), gfp);
		} else {
			sscanf(a2, "%d", &n);
			ipv4_list_add_net(od, ipv4_stohl(a1), n, gfp);
		}
		/* ------------------------------------ */
		break;
	case ':':
	case '-':
		/* 10.10.20.0-10.20.0.255 */
		/* ------------------------------------ */
		ipv4_list_add_range(od, ipv4_stohl(a1), ipv4_stohl(a2), gfp);
		/* ------------------------------------ */
		break;
	default:
		if (is_ipv4_addr(a1)) {
			/* Single IP address. */
			u32 ip = ipv4_stohl(a1);
			/* ------------------------------------ */
			ipv4_list_add_range(od, ip, ip, gfp);
			/* ------------------------------------ */
		} else {
			fprintf(stderr, "Invalid IP address '%s'.\n", a1);
			return -EINVAL;
		}
		break;
	}
	return 0;
}