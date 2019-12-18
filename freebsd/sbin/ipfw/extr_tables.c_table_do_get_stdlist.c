#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_6__ {size_t size; int /*<<< orphan*/  opheader; } ;
typedef  TYPE_1__ ipfw_obj_lheader ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 TYPE_1__* calloc (int,size_t) ; 
 scalar_t__ do_get3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
table_do_get_stdlist(uint16_t opcode, ipfw_obj_lheader **polh)
{
	ipfw_obj_lheader req, *olh;
	size_t sz;

	memset(&req, 0, sizeof(req));
	sz = sizeof(req);

	if (do_get3(opcode, &req.opheader, &sz) != 0)
		if (errno != ENOMEM)
			return (errno);

	sz = req.size;
	if ((olh = calloc(1, sz)) == NULL)
		return (ENOMEM);

	olh->size = sz;
	if (do_get3(opcode, &olh->opheader, &sz) != 0) {
		free(olh);
		return (errno);
	}

	*polh = olh;
	return (0);
}