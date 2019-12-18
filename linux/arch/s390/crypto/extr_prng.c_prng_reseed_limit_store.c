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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ PRNG_MODE_SHA512 ; 
 unsigned int PRNG_RESEED_LIMIT_SHA512_LOWER ; 
 unsigned int PRNG_RESEED_LIMIT_TDES_LOWER ; 
 scalar_t__ prng_mode ; 
 unsigned int prng_reseed_limit ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static ssize_t prng_reseed_limit_store(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t count)
{
	unsigned limit;

	if (sscanf(buf, "%u\n", &limit) != 1)
		return -EINVAL;

	if (prng_mode == PRNG_MODE_SHA512) {
		if (limit < PRNG_RESEED_LIMIT_SHA512_LOWER)
			return -EINVAL;
	} else {
		if (limit < PRNG_RESEED_LIMIT_TDES_LOWER)
			return -EINVAL;
	}

	prng_reseed_limit = limit;

	return count;
}