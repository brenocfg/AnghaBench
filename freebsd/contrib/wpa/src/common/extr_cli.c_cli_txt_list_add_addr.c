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
typedef  int /*<<< orphan*/  u8 ;
struct dl_list {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MACSTR ; 
 int cli_txt_list_add (struct dl_list*,char*) ; 
 scalar_t__ hwaddr_aton (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cli_txt_list_add_addr(struct dl_list *txt_list, const char *txt)
{
	u8 addr[ETH_ALEN];
	char buf[18];

	if (hwaddr_aton(txt, addr) < 0)
		return -1;
	os_snprintf(buf, sizeof(buf), MACSTR, MAC2STR(addr));
	return cli_txt_list_add(txt_list, buf);
}