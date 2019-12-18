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
struct stm32_hash_request_ctx {int dummy; } ;
struct stm32_hash_dev {int flags; scalar_t__ err; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_CR ; 
 int /*<<< orphan*/  HASH_CR_INIT ; 
 int /*<<< orphan*/  HASH_DIN ; 
 int HASH_FLAGS_INIT ; 
 int /*<<< orphan*/  HASH_IMR ; 
 int /*<<< orphan*/  HASH_STR ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_hash_write (struct stm32_hash_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_hash_hw_init(struct stm32_hash_dev *hdev,
			      struct stm32_hash_request_ctx *rctx)
{
	pm_runtime_get_sync(hdev->dev);

	if (!(HASH_FLAGS_INIT & hdev->flags)) {
		stm32_hash_write(hdev, HASH_CR, HASH_CR_INIT);
		stm32_hash_write(hdev, HASH_STR, 0);
		stm32_hash_write(hdev, HASH_DIN, 0);
		stm32_hash_write(hdev, HASH_IMR, 0);
		hdev->err = 0;
	}

	return 0;
}