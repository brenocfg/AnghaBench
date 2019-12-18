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
typedef  int uint64_t ;
struct cf_setting {int freq; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int EINVAL ; 
 int PCR_HALF ; 
 int PCR_QUARTER ; 
 int /*<<< orphan*/  SCOM_PSR ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 
 int read_scom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcr_get(device_t dev, struct cf_setting *set)
{
	uint64_t psr;

	if (set == NULL)
		return (EINVAL);

	memset(set, CPUFREQ_VAL_UNKNOWN, sizeof(*set));

	psr = read_scom(SCOM_PSR);

	/* We want bits 6 and 7 */
	psr = (psr >> 56) & 3;

	set->freq = 10000;
	if (psr == PCR_HALF)
		set->freq = 5000;
	else if (psr == PCR_QUARTER)
		set->freq = 2500;

	set->dev = dev;

	return (0);
}