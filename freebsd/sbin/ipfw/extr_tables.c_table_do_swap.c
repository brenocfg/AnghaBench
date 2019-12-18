#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tbuf ;
typedef  int /*<<< orphan*/  ipfw_obj_ntlv ;
struct TYPE_5__ {int /*<<< orphan*/  set; } ;
struct TYPE_6__ {int /*<<< orphan*/  opheader; TYPE_1__ ntlv; } ;
typedef  TYPE_2__ ipfw_obj_header ;

/* Variables and functions */
 int /*<<< orphan*/  IP_FW_TABLE_XSWAP ; 
 int do_set3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  table_fill_ntlv (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
table_do_swap(ipfw_obj_header *oh, char *second)
{
	char tbuf[sizeof(ipfw_obj_header) + sizeof(ipfw_obj_ntlv)];
	int error;

	memset(tbuf, 0, sizeof(tbuf));
	memcpy(tbuf, oh, sizeof(*oh));
	oh = (ipfw_obj_header *)tbuf;
	table_fill_ntlv((ipfw_obj_ntlv *)(oh + 1), second, oh->ntlv.set, 1);

	error = do_set3(IP_FW_TABLE_XSWAP, &oh->opheader, sizeof(tbuf));

	return (error);
}