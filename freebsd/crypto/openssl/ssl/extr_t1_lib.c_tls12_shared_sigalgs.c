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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  SIGALG_LOOKUP ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_SECOP_SIGALG_SHARED ; 
 int /*<<< orphan*/  tls12_sigalg_allowed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * tls1_lookup_sigalg (scalar_t__ const) ; 

__attribute__((used)) static size_t tls12_shared_sigalgs(SSL *s, const SIGALG_LOOKUP **shsig,
                                   const uint16_t *pref, size_t preflen,
                                   const uint16_t *allow, size_t allowlen)
{
    const uint16_t *ptmp, *atmp;
    size_t i, j, nmatch = 0;
    for (i = 0, ptmp = pref; i < preflen; i++, ptmp++) {
        const SIGALG_LOOKUP *lu = tls1_lookup_sigalg(*ptmp);

        /* Skip disabled hashes or signature algorithms */
        if (!tls12_sigalg_allowed(s, SSL_SECOP_SIGALG_SHARED, lu))
            continue;
        for (j = 0, atmp = allow; j < allowlen; j++, atmp++) {
            if (*ptmp == *atmp) {
                nmatch++;
                if (shsig)
                    *shsig++ = lu;
                break;
            }
        }
    }
    return nmatch;
}