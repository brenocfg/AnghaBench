#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; } ;
typedef  TYPE_1__ ipfw_xtable_info ;
struct TYPE_12__ {int version; } ;
struct TYPE_11__ {TYPE_8__ opheader; } ;
typedef  TYPE_2__ ipfw_obj_header ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  IP_FW_TABLE_XLIST ; 
 TYPE_2__* calloc (int,size_t) ; 
 scalar_t__ do_get3 (int /*<<< orphan*/ ,TYPE_8__*,size_t*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  table_fill_objheader (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int
table_do_get_list(ipfw_xtable_info *i, ipfw_obj_header **poh)
{
	ipfw_obj_header *oh;
	size_t sz;
	int c;

	sz = 0;
	oh = NULL;
	for (c = 0; c < 8; c++) {
		if (sz < i->size)
			sz = i->size + 44;
		if (oh != NULL)
			free(oh);
		if ((oh = calloc(1, sz)) == NULL)
			continue;
		table_fill_objheader(oh, i);
		oh->opheader.version = 1; /* Current version */
		if (do_get3(IP_FW_TABLE_XLIST, &oh->opheader, &sz) == 0) {
			*poh = oh;
			return (0);
		}

		if (errno != ENOMEM)
			break;
	}
	free(oh);

	return (errno);
}