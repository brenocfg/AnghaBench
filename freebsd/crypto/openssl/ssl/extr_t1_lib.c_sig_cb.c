#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sigalgcnt; scalar_t__* sigalgs; } ;
typedef  TYPE_1__ sig_cb_st ;
typedef  int /*<<< orphan*/  etmp ;
struct TYPE_6__ {scalar_t__ sigalg; int hash; int sig; int /*<<< orphan*/ * name; } ;
typedef  TYPE_2__ SIGALG_LOOKUP ;

/* Variables and functions */
 int NID_undef ; 
 size_t OSSL_NELEM (TYPE_2__*) ; 
 int TLS_MAX_SIGALGCNT ; 
 int TLS_MAX_SIGSTRING_LEN ; 
 int /*<<< orphan*/  get_sigorhash (int*,int*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 TYPE_2__* sigalg_lookup_tbl ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sig_cb(const char *elem, int len, void *arg)
{
    sig_cb_st *sarg = arg;
    size_t i;
    const SIGALG_LOOKUP *s;
    char etmp[TLS_MAX_SIGSTRING_LEN], *p;
    int sig_alg = NID_undef, hash_alg = NID_undef;
    if (elem == NULL)
        return 0;
    if (sarg->sigalgcnt == TLS_MAX_SIGALGCNT)
        return 0;
    if (len > (int)(sizeof(etmp) - 1))
        return 0;
    memcpy(etmp, elem, len);
    etmp[len] = 0;
    p = strchr(etmp, '+');
    /*
     * We only allow SignatureSchemes listed in the sigalg_lookup_tbl;
     * if there's no '+' in the provided name, look for the new-style combined
     * name.  If not, match both sig+hash to find the needed SIGALG_LOOKUP.
     * Just sig+hash is not unique since TLS 1.3 adds rsa_pss_pss_* and
     * rsa_pss_rsae_* that differ only by public key OID; in such cases
     * we will pick the _rsae_ variant, by virtue of them appearing earlier
     * in the table.
     */
    if (p == NULL) {
        for (i = 0, s = sigalg_lookup_tbl; i < OSSL_NELEM(sigalg_lookup_tbl);
             i++, s++) {
            if (s->name != NULL && strcmp(etmp, s->name) == 0) {
                sarg->sigalgs[sarg->sigalgcnt++] = s->sigalg;
                break;
            }
        }
        if (i == OSSL_NELEM(sigalg_lookup_tbl))
            return 0;
    } else {
        *p = 0;
        p++;
        if (*p == 0)
            return 0;
        get_sigorhash(&sig_alg, &hash_alg, etmp);
        get_sigorhash(&sig_alg, &hash_alg, p);
        if (sig_alg == NID_undef || hash_alg == NID_undef)
            return 0;
        for (i = 0, s = sigalg_lookup_tbl; i < OSSL_NELEM(sigalg_lookup_tbl);
             i++, s++) {
            if (s->hash == hash_alg && s->sig == sig_alg) {
                sarg->sigalgs[sarg->sigalgcnt++] = s->sigalg;
                break;
            }
        }
        if (i == OSSL_NELEM(sigalg_lookup_tbl))
            return 0;
    }

    /* Reject duplicates */
    for (i = 0; i < sarg->sigalgcnt - 1; i++) {
        if (sarg->sigalgs[i] == sarg->sigalgs[sarg->sigalgcnt - 1]) {
            sarg->sigalgcnt--;
            return 0;
        }
    }
    return 1;
}