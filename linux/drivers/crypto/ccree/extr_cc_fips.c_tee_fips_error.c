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

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ fips_enabled ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static inline void tee_fips_error(struct device *dev)
{
	if (fips_enabled)
		panic("ccree: TEE reported cryptographic error in fips mode!\n");
	else
		dev_err(dev, "TEE reported error!\n");
}