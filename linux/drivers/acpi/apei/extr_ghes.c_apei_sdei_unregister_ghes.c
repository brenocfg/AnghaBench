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
 int sdei_unregister_ghes (struct ghes*) ; 

__attribute__((used)) static int apei_sdei_unregister_ghes(struct ghes *ghes)
{
	if (!IS_ENABLED(CONFIG_ARM_SDE_INTERFACE))
		return -EOPNOTSUPP;

	return sdei_unregister_ghes(ghes);
}