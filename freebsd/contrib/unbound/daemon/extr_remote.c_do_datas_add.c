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
struct local_zones {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  perform_data_add (int /*<<< orphan*/ *,struct local_zones*,char*) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ ssl_read_line (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
do_datas_add(RES* ssl, struct local_zones* zones)
{
	char buf[2048];
	int num = 0;
	while(ssl_read_line(ssl, buf, sizeof(buf))) {
		if(buf[0] == 0x04 && buf[1] == 0)
			break; /* end of transmission */
		if(!perform_data_add(ssl, zones, buf)) {
			if(!ssl_printf(ssl, "error for input line: %s\n", buf))
				return;
		}
		else
			num++;
	}
	(void)ssl_printf(ssl, "added %d datas\n", num);
}