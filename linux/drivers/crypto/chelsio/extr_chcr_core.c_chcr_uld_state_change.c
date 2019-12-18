#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct uld_ctx {TYPE_1__ dev; } ;
typedef  enum cxgb4_state { ____Placeholder_cxgb4_state } cxgb4_state ;

/* Variables and functions */
 int /*<<< orphan*/  CHCR_INIT ; 
#define  CXGB4_STATE_DETACH 131 
#define  CXGB4_STATE_DOWN 130 
#define  CXGB4_STATE_START_RECOVERY 129 
#define  CXGB4_STATE_UP 128 
 int /*<<< orphan*/  chcr_detach_device (struct uld_ctx*) ; 
 int /*<<< orphan*/  chcr_dev_add (struct uld_ctx*) ; 
 int start_crypto () ; 

__attribute__((used)) static int chcr_uld_state_change(void *handle, enum cxgb4_state state)
{
	struct uld_ctx *u_ctx = handle;
	int ret = 0;

	switch (state) {
	case CXGB4_STATE_UP:
		if (u_ctx->dev.state != CHCR_INIT) {
			// ALready Initialised.
			return 0;
		}
		chcr_dev_add(u_ctx);
		ret = start_crypto();
		break;

	case CXGB4_STATE_DETACH:
		chcr_detach_device(u_ctx);
		break;

	case CXGB4_STATE_START_RECOVERY:
	case CXGB4_STATE_DOWN:
	default:
		break;
	}
	return ret;
}