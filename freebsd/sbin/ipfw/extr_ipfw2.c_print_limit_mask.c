#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct buf_pr {int dummy; } ;
struct _s_x {int x; int /*<<< orphan*/  s; } ;
struct TYPE_3__ {int limit_mask; int /*<<< orphan*/  conn_limit; } ;
typedef  TYPE_1__ ipfw_insn_limit ;

/* Variables and functions */
 int /*<<< orphan*/  bprint_uint_arg (struct buf_pr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bprintf (struct buf_pr*,char*,char const*,int /*<<< orphan*/ ) ; 
 struct _s_x* limit_masks ; 

__attribute__((used)) static void
print_limit_mask(struct buf_pr *bp, const ipfw_insn_limit *limit)
{
	struct _s_x *p = limit_masks;
	char const *comma = " ";
	uint8_t x;

	for (x = limit->limit_mask; p->x != 0; p++) {
		if ((x & p->x) == p->x) {
			x &= ~p->x;
			bprintf(bp, "%s%s", comma, p->s);
			comma = ",";
		}
	}
	bprint_uint_arg(bp, " ", limit->conn_limit);
}