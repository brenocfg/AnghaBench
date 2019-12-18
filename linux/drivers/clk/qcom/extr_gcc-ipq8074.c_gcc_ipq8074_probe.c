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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_ipq8074_desc ; 
 int qcom_cc_probe (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gcc_ipq8074_probe(struct platform_device *pdev)
{
	return qcom_cc_probe(pdev, &gcc_ipq8074_desc);
}