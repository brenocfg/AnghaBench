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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  secret ;
typedef  int /*<<< orphan*/  ptls_hash_algorithm_t ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;
typedef  int /*<<< orphan*/  ptls_aead_algorithm_t ;
typedef  int /*<<< orphan*/  p_version ;

/* Variables and functions */
 char* BENCH_MODE ; 
 int OPENSSL_VERSION_NUMBER ; 
 int PTLS_ERROR_NO_MEMORY ; 
 int PTLS_MAX_SECRET_SIZE ; 
 double bench_mbps (scalar_t__,size_t,size_t) ; 
 int bench_run_one (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,int,char*,int,char const*,char*,char const*,int,int,int,int,double,double) ; 
 int /*<<< orphan*/  ptls_aead_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ptls_aead_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,char) ; 
 int /*<<< orphan*/  sprintf_s (char*,int,char*,int,int,int,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int bench_run_aead(char  * OS, char * HW, int basic_ref, uint64_t s0, const char *provider, const char *algo_name, ptls_aead_algorithm_t *aead, ptls_hash_algorithm_t *hash, size_t n, size_t l, uint64_t *s)
{
    int ret = 0;

    uint8_t secret[PTLS_MAX_SECRET_SIZE];
    ptls_aead_context_t *e;
    ptls_aead_context_t *d;
    uint64_t t_e = 0;
    uint64_t t_d = 0;
    char p_version[128];

    /* Document library version as it may have impact on performance */
    p_version[0] = 0;

    if (strcmp(provider, "openssl") == 0) {
        /*
         * OPENSSL_VERSION_NUMBER is a combination of the major, minor and patch version 
         * into a single integer 0xMNNFFPP0L, where M is major, NN is minor, PP is patch
         */
        uint32_t combined = OPENSSL_VERSION_NUMBER;
        int M = combined >> 28;
        int NN = (combined >> 20) & 0xFF;
        int FF = (combined >> 12) & 0xFF;
        int PP = (combined >> 4) & 0xFF;
        char letter = 'a' - 1 + PP;

#ifdef _WINDOWS
        (void)sprintf_s(p_version, sizeof(p_version), "%d.%d.%d%c", M, NN, FF, letter);
#else
        (void)sprintf(p_version, "%d.%d.%d%c", M, NN, FF, letter);
#endif
    }

    *s += s0;

    memset(secret, 'z', sizeof(secret));
    e = ptls_aead_new(aead, hash, 1, secret, NULL);
    d = ptls_aead_new(aead, hash, 0, secret, NULL);

    if (e == NULL || d == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
    } else {
        ret = bench_run_one(e, d, n, l, &t_e, &t_d, s);
        if (ret == 0) {
            printf("%s, %s, %d, %s, %d, %s, %s, %s, %d, %d, %d, %d, %.2f, %.2f\n", OS, HW, (int)(8 * sizeof(size_t)), BENCH_MODE, basic_ref,
                   provider, p_version, algo_name, (int)n, (int)l, (int)t_e, (int)t_d, bench_mbps(t_e, l, n),
                   bench_mbps(t_d, l, n));
        }
    }

    if (e) {
        ptls_aead_free(e);
    }

    if (d) {
        ptls_aead_free(d);
    }

    return ret;
}