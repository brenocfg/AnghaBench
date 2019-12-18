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
struct dmaengine_result {int /*<<< orphan*/  residue; int /*<<< orphan*/  result; } ;
struct dmaengine_desc_callback {int /*<<< orphan*/  callback_param; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* callback_result ) (int /*<<< orphan*/ ,struct dmaengine_result const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TRANS_NOERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct dmaengine_result const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
dmaengine_desc_callback_invoke(struct dmaengine_desc_callback *cb,
			       const struct dmaengine_result *result)
{
	struct dmaengine_result dummy_result = {
		.result = DMA_TRANS_NOERROR,
		.residue = 0
	};

	if (cb->callback_result) {
		if (!result)
			result = &dummy_result;
		cb->callback_result(cb->callback_param, result);
	} else if (cb->callback) {
		cb->callback(cb->callback_param);
	}
}