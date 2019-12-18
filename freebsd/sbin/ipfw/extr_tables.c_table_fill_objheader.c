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
struct TYPE_5__ {int /*<<< orphan*/  set; int /*<<< orphan*/  tablename; } ;
typedef  TYPE_1__ ipfw_xtable_info ;
struct TYPE_6__ {int idx; int /*<<< orphan*/  ntlv; } ;
typedef  TYPE_2__ ipfw_obj_header ;

/* Variables and functions */
 int /*<<< orphan*/  table_fill_ntlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
table_fill_objheader(ipfw_obj_header *oh, ipfw_xtable_info *i)
{

	oh->idx = 1;
	table_fill_ntlv(&oh->ntlv, i->tablename, i->set, 1);
}