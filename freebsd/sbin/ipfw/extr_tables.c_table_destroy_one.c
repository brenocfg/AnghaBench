#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  set; int /*<<< orphan*/  tablename; } ;
typedef  TYPE_1__ ipfw_xtable_info ;
struct TYPE_7__ {int /*<<< orphan*/  ntlv; } ;
typedef  TYPE_2__ ipfw_obj_header ;
struct TYPE_8__ {scalar_t__ do_quiet; } ;

/* Variables and functions */
 TYPE_5__ co ; 
 scalar_t__ table_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  table_fill_ntlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
table_destroy_one(ipfw_xtable_info *i, void *arg)
{
	ipfw_obj_header *oh;

	oh = (ipfw_obj_header *)arg;
	table_fill_ntlv(&oh->ntlv, i->tablename, i->set, 1);
	if (table_destroy(oh) != 0) {
		if (co.do_quiet == 0)
			warn("failed to destroy table(%s) in set %u",
			    i->tablename, i->set);
		return (-1);
	}
	return (0);
}