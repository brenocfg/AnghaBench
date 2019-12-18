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
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DH_new () ; 
 int /*<<< orphan*/  DH_set0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DH *
dh_new_group_asc(const char *gen, const char *modulus)
{
	DH *dh;
	BIGNUM *dh_p = NULL, *dh_g = NULL;

	if ((dh = DH_new()) == NULL)
		return NULL;
	if (BN_hex2bn(&dh_p, modulus) == 0 ||
	    BN_hex2bn(&dh_g, gen) == 0)
		goto fail;
	if (!DH_set0_pqg(dh, dh_p, NULL, dh_g))
		goto fail;
	return dh;
 fail:
	DH_free(dh);
	BN_clear_free(dh_p);
	BN_clear_free(dh_g);
	return NULL;
}