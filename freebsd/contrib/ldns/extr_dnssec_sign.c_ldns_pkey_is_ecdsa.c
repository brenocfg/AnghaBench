#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 scalar_t__ EC_GROUP_get_curve_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_EC ; 
 scalar_t__ EVP_PKEY_base_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_type (int /*<<< orphan*/ ) ; 
 scalar_t__ NID_X9_62_prime256v1 ; 
 scalar_t__ NID_secp384r1 ; 
 TYPE_1__* key ; 

__attribute__((used)) static int
ldns_pkey_is_ecdsa(EVP_PKEY* pkey)
{
        EC_KEY* ec;
        const EC_GROUP* g;
#ifdef HAVE_EVP_PKEY_BASE_ID
        if(EVP_PKEY_base_id(pkey) != EVP_PKEY_EC)
                return 0;
#else
        if(EVP_PKEY_type(key->type) != EVP_PKEY_EC)
                return 0;
#endif
        ec = EVP_PKEY_get1_EC_KEY(pkey);
        g = EC_KEY_get0_group(ec);
        if(!g) {
                EC_KEY_free(ec);
                return 0;
        }
        if(EC_GROUP_get_curve_name(g) == NID_X9_62_prime256v1) {
                EC_KEY_free(ec);
                return 32; /* 256/8 */
	}
        if(EC_GROUP_get_curve_name(g) == NID_secp384r1) {
                EC_KEY_free(ec);
                return 48; /* 384/8 */
        }
        /* downref the eckey, the original is still inside the pkey */
        EC_KEY_free(ec);
        return 0;
}