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
struct ecc_curve {int dummy; } ;

/* Variables and functions */
#define  ECC_CURVE_NIST_P192 129 
#define  ECC_CURVE_NIST_P256 128 
 int /*<<< orphan*/  fips_enabled ; 
 struct ecc_curve const nist_p192 ; 
 struct ecc_curve const nist_p256 ; 

__attribute__((used)) static inline const struct ecc_curve *ecc_get_curve(unsigned int curve_id)
{
	switch (curve_id) {
	/* In FIPS mode only allow P256 and higher */
	case ECC_CURVE_NIST_P192:
		return fips_enabled ? NULL : &nist_p192;
	case ECC_CURVE_NIST_P256:
		return &nist_p256;
	default:
		return NULL;
	}
}