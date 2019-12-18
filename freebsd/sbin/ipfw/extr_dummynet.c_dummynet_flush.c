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
struct dn_id {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  oid ;

/* Variables and functions */
 int /*<<< orphan*/  DN_API_VERSION ; 
 int /*<<< orphan*/  DN_CMD_FLUSH ; 
 int /*<<< orphan*/  IP_DUMMYNET3 ; 
 int /*<<< orphan*/  do_cmd (int /*<<< orphan*/ ,struct dn_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_fill (struct dn_id*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dummynet_flush(void)
{
	struct dn_id oid;
	oid_fill(&oid, sizeof(oid), DN_CMD_FLUSH, DN_API_VERSION);
	do_cmd(IP_DUMMYNET3, &oid, oid.len);
}