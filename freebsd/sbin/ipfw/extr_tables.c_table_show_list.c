#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {char* tablename; int set; scalar_t__ count; } ;
typedef  TYPE_2__ ipfw_xtable_info ;
struct TYPE_6__ {scalar_t__ length; } ;
struct TYPE_8__ {TYPE_1__ head; } ;
typedef  TYPE_3__ ipfw_obj_tentry ;
typedef  int /*<<< orphan*/  ipfw_obj_header ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  table_show_entry (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void
table_show_list(ipfw_obj_header *oh, int need_header)
{
	ipfw_obj_tentry *tent;
	uint32_t count;
	ipfw_xtable_info *i;

	i = (ipfw_xtable_info *)(oh + 1);
	tent = (ipfw_obj_tentry *)(i + 1);

	if (need_header)
		printf("--- table(%s), set(%u) ---\n", i->tablename, i->set);

	count = i->count;
	while (count > 0) {
		table_show_entry(i, tent);
		tent = (ipfw_obj_tentry *)((caddr_t)tent + tent->head.length);
		count--;
	}
}