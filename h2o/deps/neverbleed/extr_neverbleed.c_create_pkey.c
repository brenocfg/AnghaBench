#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_neverbleed_rsa_exdata_t {size_t key_index; TYPE_1__* nb; } ;
struct TYPE_3__ {int /*<<< orphan*/  engine; } ;
typedef  TYPE_1__ neverbleed_t ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set1_RSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_FLAG_EXT_PKEY ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new_method (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_set_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct st_neverbleed_rsa_exdata_t*) ; 
 int /*<<< orphan*/  RSA_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct st_neverbleed_rsa_exdata_t* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static EVP_PKEY *create_pkey(neverbleed_t *nb, size_t key_index, const char *ebuf, const char *nbuf)
{
    struct st_neverbleed_rsa_exdata_t *exdata;
    RSA *rsa;
    EVP_PKEY *pkey;
    BIGNUM *e = NULL, *n = NULL;

    if ((exdata = malloc(sizeof(*exdata))) == NULL) {
        fprintf(stderr, "no memory\n");
        abort();
    }
    exdata->nb = nb;
    exdata->key_index = key_index;

    rsa = RSA_new_method(nb->engine);
    RSA_set_ex_data(rsa, 0, exdata);
    if (BN_hex2bn(&e, ebuf) == 0) {
        fprintf(stderr, "failed to parse e:%s\n", ebuf);
        abort();
    }
    if (BN_hex2bn(&n, nbuf) == 0) {
        fprintf(stderr, "failed to parse n:%s\n", nbuf);
        abort();
    }
    RSA_set0_key(rsa, n, e, NULL);
    RSA_set_flags(rsa, RSA_FLAG_EXT_PKEY);

    pkey = EVP_PKEY_new();
    EVP_PKEY_set1_RSA(pkey, rsa);
    RSA_free(rsa);

    return pkey;
}