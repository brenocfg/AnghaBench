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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  (* ub_callback_type ) (void*,int,struct ub_result*) ;
struct ub_result {int dummy; } ;
struct ub_ctx {int dummy; } ;

/* Variables and functions */
 int process_answer_detail (struct ub_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*,int,struct ub_result*),void**,int*,struct ub_result**) ; 
 int /*<<< orphan*/  stub1 (void*,int,struct ub_result*) ; 

__attribute__((used)) static int
process_answer(struct ub_ctx* ctx, uint8_t* msg, uint32_t len)
{
	int err;
	ub_callback_type cb;
	void* cbarg;
	struct ub_result* res;
	int r;

	r = process_answer_detail(ctx, msg, len, &cb, &cbarg, &err, &res);

	/* no locks held while calling callback, so that library is
	 * re-entrant. */
	if(r == 2)
		(*cb)(cbarg, err, res);

	return r;
}