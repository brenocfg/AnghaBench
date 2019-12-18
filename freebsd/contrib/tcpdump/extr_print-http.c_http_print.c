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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  RESP_CODE_SECOND_TOKEN ; 
 int /*<<< orphan*/  httpcmds ; 
 int /*<<< orphan*/  txtproto_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
http_print(netdissect_options *ndo, const u_char *pptr, u_int len)
{
	txtproto_print(ndo, pptr, len, "http", httpcmds, RESP_CODE_SECOND_TOKEN);
}