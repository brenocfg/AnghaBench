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
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  EC_GROUP_get0_generator (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_get0_private_key (int /*<<< orphan*/ *) ; 
 scalar_t__ EC_KEY_set_public_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
ldns_EC_KEY_calc_public(EC_KEY* ec)
{
        EC_POINT* pub_key;
        const EC_GROUP* group;
        group = EC_KEY_get0_group(ec);
        pub_key = EC_POINT_new(group);
        if(!pub_key) return 0;
        if(!EC_POINT_copy(pub_key, EC_GROUP_get0_generator(group))) {
                EC_POINT_free(pub_key);
                return 0;
        }
        if(!EC_POINT_mul(group, pub_key, EC_KEY_get0_private_key(ec),
                NULL, NULL, NULL)) {
                EC_POINT_free(pub_key);
                return 0;
        }
        if(EC_KEY_set_public_key(ec, pub_key) == 0) {
                EC_POINT_free(pub_key);
                return 0;
        }
        EC_POINT_free(pub_key);
        return 1;
}