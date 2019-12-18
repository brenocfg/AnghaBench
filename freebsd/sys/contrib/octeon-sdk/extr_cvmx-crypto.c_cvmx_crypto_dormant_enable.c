#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  key; } ;
struct TYPE_4__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_rnm_eer_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_RNM_EER_KEY ; 
 int /*<<< orphan*/  OCTEON_FEATURE_CRYPTO ; 
 int /*<<< orphan*/  OCTEON_FEATURE_DORM_CRYPTO ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int octeon_has_feature (int /*<<< orphan*/ ) ; 

int cvmx_crypto_dormant_enable(uint64_t key)
{
    if (octeon_has_feature(OCTEON_FEATURE_CRYPTO))
        return 1;

    if (octeon_has_feature(OCTEON_FEATURE_DORM_CRYPTO)) {
        cvmx_rnm_eer_key_t v;
        v.s.key = key;
        cvmx_write_csr(CVMX_RNM_EER_KEY, v.u64);
    }

    return octeon_has_feature(OCTEON_FEATURE_CRYPTO);
}