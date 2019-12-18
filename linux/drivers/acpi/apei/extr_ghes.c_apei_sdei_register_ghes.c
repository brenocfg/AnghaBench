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
struct ghes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARM_SDE_INTERFACE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghes_sdei_critical_callback ; 
 int /*<<< orphan*/  ghes_sdei_normal_callback ; 
 int sdei_register_ghes (struct ghes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apei_sdei_register_ghes(struct ghes *ghes)
{
	if (!IS_ENABLED(CONFIG_ARM_SDE_INTERFACE))
		return -EOPNOTSUPP;

	return sdei_register_ghes(ghes, ghes_sdei_normal_callback,
				 ghes_sdei_critical_callback);
}