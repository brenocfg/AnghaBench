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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ftpm_tee_private {int /*<<< orphan*/  ctx; int /*<<< orphan*/  session; int /*<<< orphan*/  shm; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ftpm_tee_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tee_client_close_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tee_client_close_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tee_shm_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_chip_unregister (TYPE_1__*) ; 

__attribute__((used)) static int ftpm_tee_remove(struct platform_device *pdev)
{
	struct ftpm_tee_private *pvt_data = dev_get_drvdata(&pdev->dev);

	/* Release the chip */
	tpm_chip_unregister(pvt_data->chip);

	/* frees chip */
	put_device(&pvt_data->chip->dev);

	/* Free the shared memory pool */
	tee_shm_free(pvt_data->shm);

	/* close the existing session with fTPM TA*/
	tee_client_close_session(pvt_data->ctx, pvt_data->session);

	/* close the context with TEE driver */
	tee_client_close_context(pvt_data->ctx);

	/* memory allocated with devm_kzalloc() is freed automatically */

	return 0;
}