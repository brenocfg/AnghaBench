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
typedef  int /*<<< orphan*/  u_char ;
struct mgmt_header_t {int /*<<< orphan*/  sa; int /*<<< orphan*/  da; int /*<<< orphan*/  bssid; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etheraddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mgmt_header_print(netdissect_options *ndo, const u_char *p)
{
	const struct mgmt_header_t *hp = (const struct mgmt_header_t *) p;

	ND_PRINT((ndo, "BSSID:%s DA:%s SA:%s ",
	    etheraddr_string(ndo, (hp)->bssid), etheraddr_string(ndo, (hp)->da),
	    etheraddr_string(ndo, (hp)->sa)));
}