#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct opcode_obj_rewrite {scalar_t__ (* classifier ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ ipfw_insn ;

/* Variables and functions */
 scalar_t__ find_op_rw_range (int /*<<< orphan*/ ,struct opcode_obj_rewrite**,struct opcode_obj_rewrite**) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct opcode_obj_rewrite *
find_op_rw(ipfw_insn *cmd, uint16_t *puidx, uint8_t *ptype)
{
	struct opcode_obj_rewrite *rw, *lo, *hi;
	uint16_t uidx;
	uint8_t subtype;

	if (find_op_rw_range(cmd->opcode, &lo, &hi) != 0)
		return (NULL);

	for (rw = lo; rw <= hi; rw++) {
		if (rw->classifier(cmd, &uidx, &subtype) == 0) {
			if (puidx != NULL)
				*puidx = uidx;
			if (ptype != NULL)
				*ptype = subtype;
			return (rw);
		}
	}

	return (NULL);
}