#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xbuf ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ipfw_xtable_info ;
struct TYPE_11__ {int length; } ;
struct TYPE_13__ {int idx; TYPE_1__ head; } ;
typedef  TYPE_3__ ipfw_obj_tentry ;
struct TYPE_12__ {int /*<<< orphan*/  type; } ;
struct TYPE_14__ {int /*<<< orphan*/  opheader; TYPE_2__ ntlv; } ;
typedef  TYPE_4__ ipfw_obj_header ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IP_FW_TABLE_XFIND ; 
 scalar_t__ do_get3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tentry_fill_key (TYPE_4__*,TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
table_do_lookup(ipfw_obj_header *oh, char *key, ipfw_xtable_info *xi,
    ipfw_obj_tentry *xtent)
{
	char xbuf[sizeof(ipfw_obj_header) + sizeof(ipfw_obj_tentry)];
	ipfw_obj_tentry *tent;
	uint8_t type;
	uint32_t vmask;
	size_t sz;

	memcpy(xbuf, oh, sizeof(*oh));
	oh = (ipfw_obj_header *)xbuf;
	tent = (ipfw_obj_tentry *)(oh + 1);

	memset(tent, 0, sizeof(*tent));
	tent->head.length = sizeof(*tent);
	tent->idx = 1;

	tentry_fill_key(oh, tent, key, 0, &type, &vmask, xi);
	oh->ntlv.type = type;

	sz = sizeof(xbuf);
	if (do_get3(IP_FW_TABLE_XFIND, &oh->opheader, &sz) != 0)
		return (errno);

	if (sz < sizeof(xbuf))
		return (EINVAL);

	*xtent = *tent;

	return (0);
}