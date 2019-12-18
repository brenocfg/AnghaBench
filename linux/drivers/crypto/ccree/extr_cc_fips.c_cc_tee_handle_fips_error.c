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
struct device {int dummy; } ;
struct cc_drvdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cc_get_tee_fips_status (struct cc_drvdata*) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  tee_fips_error (struct device*) ; 

void cc_tee_handle_fips_error(struct cc_drvdata *p_drvdata)
{
	struct device *dev = drvdata_to_dev(p_drvdata);

	if (!cc_get_tee_fips_status(p_drvdata))
		tee_fips_error(dev);
}