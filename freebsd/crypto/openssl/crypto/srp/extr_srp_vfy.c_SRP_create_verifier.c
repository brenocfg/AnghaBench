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
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {char* id; int /*<<< orphan*/ * g; int /*<<< orphan*/ * N; } ;
typedef  TYPE_1__ SRP_gN ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_bn2bin (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int BN_num_bytes (int /*<<< orphan*/ *) ; 
 int MAX_LEN ; 
 int /*<<< orphan*/  OPENSSL_clear_free (char*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (int) ; 
 scalar_t__ RAND_bytes (unsigned char*,int) ; 
 int SRP_RANDOM_SALT_LEN ; 
 int /*<<< orphan*/  SRP_create_verifier_BN (char const*,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_1__* SRP_get_gN_by_id (char const*,int /*<<< orphan*/ *) ; 
 int t_fromb64 (unsigned char*,int,char const*) ; 
 int /*<<< orphan*/  t_tob64 (char*,unsigned char*,int) ; 

char *SRP_create_verifier(const char *user, const char *pass, char **salt,
                          char **verifier, const char *N, const char *g)
{
    int len;
    char *result = NULL, *vf = NULL;
    const BIGNUM *N_bn = NULL, *g_bn = NULL;
    BIGNUM *N_bn_alloc = NULL, *g_bn_alloc = NULL, *s = NULL, *v = NULL;
    unsigned char tmp[MAX_LEN];
    unsigned char tmp2[MAX_LEN];
    char *defgNid = NULL;
    int vfsize = 0;

    if ((user == NULL) ||
        (pass == NULL) || (salt == NULL) || (verifier == NULL))
        goto err;

    if (N) {
        if ((len = t_fromb64(tmp, sizeof(tmp), N)) <= 0)
            goto err;
        N_bn_alloc = BN_bin2bn(tmp, len, NULL);
        if (N_bn_alloc == NULL)
            goto err;
        N_bn = N_bn_alloc;
        if ((len = t_fromb64(tmp, sizeof(tmp) ,g)) <= 0)
            goto err;
        g_bn_alloc = BN_bin2bn(tmp, len, NULL);
        if (g_bn_alloc == NULL)
            goto err;
        g_bn = g_bn_alloc;
        defgNid = "*";
    } else {
        SRP_gN *gN = SRP_get_gN_by_id(g, NULL);
        if (gN == NULL)
            goto err;
        N_bn = gN->N;
        g_bn = gN->g;
        defgNid = gN->id;
    }

    if (*salt == NULL) {
        if (RAND_bytes(tmp2, SRP_RANDOM_SALT_LEN) <= 0)
            goto err;

        s = BN_bin2bn(tmp2, SRP_RANDOM_SALT_LEN, NULL);
    } else {
        if ((len = t_fromb64(tmp2, sizeof(tmp2), *salt)) <= 0)
            goto err;
        s = BN_bin2bn(tmp2, len, NULL);
    }
    if (s == NULL)
        goto err;

    if (!SRP_create_verifier_BN(user, pass, &s, &v, N_bn, g_bn))
        goto err;

    if (BN_bn2bin(v, tmp) < 0)
        goto err;
    vfsize = BN_num_bytes(v) * 2;
    if (((vf = OPENSSL_malloc(vfsize)) == NULL))
        goto err;
    if (!t_tob64(vf, tmp, BN_num_bytes(v)))
        goto err;

    if (*salt == NULL) {
        char *tmp_salt;

        if ((tmp_salt = OPENSSL_malloc(SRP_RANDOM_SALT_LEN * 2)) == NULL) {
            goto err;
        }
        if (!t_tob64(tmp_salt, tmp2, SRP_RANDOM_SALT_LEN)) {
            OPENSSL_free(tmp_salt);
            goto err;
        }
        *salt = tmp_salt;
    }

    *verifier = vf;
    vf = NULL;
    result = defgNid;

 err:
    BN_free(N_bn_alloc);
    BN_free(g_bn_alloc);
    OPENSSL_clear_free(vf, vfsize);
    BN_clear_free(s);
    BN_clear_free(v);
    return result;
}