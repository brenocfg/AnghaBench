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
struct ccp_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned int CCP_MAX_ERROR_CODE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/ * ccp_error_codes ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,...) ; 

void ccp_log_error(struct ccp_device *d, unsigned int e)
{
	if (WARN_ON(e >= CCP_MAX_ERROR_CODE))
		return;

	if (e < ARRAY_SIZE(ccp_error_codes))
		dev_err(d->dev, "CCP error %d: %s\n", e, ccp_error_codes[e]);
	else
		dev_err(d->dev, "CCP error %d: Unknown Error\n", e);
}