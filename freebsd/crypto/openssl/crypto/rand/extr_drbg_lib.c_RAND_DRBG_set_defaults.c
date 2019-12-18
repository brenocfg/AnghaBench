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

/* Variables and functions */
#define  NID_aes_128_ctr 130 
#define  NID_aes_192_ctr 129 
#define  NID_aes_256_ctr 128 
 int /*<<< orphan*/  RAND_F_RAND_DRBG_SET_DEFAULTS ; 
 int /*<<< orphan*/  RAND_R_UNSUPPORTED_DRBG_FLAGS ; 
 int /*<<< orphan*/  RAND_R_UNSUPPORTED_DRBG_TYPE ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int rand_drbg_flags ; 
 int rand_drbg_type ; 
 unsigned int rand_drbg_used_flags ; 

int RAND_DRBG_set_defaults(int type, unsigned int flags)
{
    int ret = 1;

    switch (type) {
    default:
        RANDerr(RAND_F_RAND_DRBG_SET_DEFAULTS, RAND_R_UNSUPPORTED_DRBG_TYPE);
        return 0;
    case NID_aes_128_ctr:
    case NID_aes_192_ctr:
    case NID_aes_256_ctr:
        break;
    }

    if ((flags & ~rand_drbg_used_flags) != 0) {
        RANDerr(RAND_F_RAND_DRBG_SET_DEFAULTS, RAND_R_UNSUPPORTED_DRBG_FLAGS);
        return 0;
    }

    rand_drbg_type  = type;
    rand_drbg_flags = flags;

    return ret;
}