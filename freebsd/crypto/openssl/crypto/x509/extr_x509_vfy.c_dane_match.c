#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {unsigned int usage; size_t mtype; unsigned int selector; unsigned int dlen; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ danetls_record ;
struct TYPE_9__ {int num_untrusted; TYPE_4__* dane; } ;
typedef  TYPE_3__ X509_STORE_CTX ;
typedef  unsigned char X509 ;
struct TYPE_10__ {int mdpth; int umask; unsigned char* mcert; TYPE_2__* mtlsa; TYPE_1__* dctx; int /*<<< orphan*/  trecs; } ;
struct TYPE_7__ {unsigned int* mdord; int /*<<< orphan*/ ** mdevp; } ;
typedef  TYPE_4__ SSL_DANE ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int DANETLS_DANE_MASK ; 
 int DANETLS_EE_MASK ; 
 size_t DANETLS_MATCHING_FULL ; 
 unsigned int DANETLS_NONE ; 
 int DANETLS_PKIX_MASK ; 
 int DANETLS_TA_MASK ; 
 int DANETLS_USAGE_BIT (unsigned int) ; 
 int /*<<< orphan*/  EVP_Digest (unsigned char*,unsigned int,unsigned char*,unsigned int*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  X509_up_ref (unsigned char*) ; 
 unsigned char* dane_i2d (unsigned char*,unsigned int,unsigned int*) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 int sk_danetls_record_num (int /*<<< orphan*/ ) ; 
 TYPE_2__* sk_danetls_record_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dane_match(X509_STORE_CTX *ctx, X509 *cert, int depth)
{
    SSL_DANE *dane = ctx->dane;
    unsigned usage = DANETLS_NONE;
    unsigned selector = DANETLS_NONE;
    unsigned ordinal = DANETLS_NONE;
    unsigned mtype = DANETLS_NONE;
    unsigned char *i2dbuf = NULL;
    unsigned int i2dlen = 0;
    unsigned char mdbuf[EVP_MAX_MD_SIZE];
    unsigned char *cmpbuf = NULL;
    unsigned int cmplen = 0;
    int i;
    int recnum;
    int matched = 0;
    danetls_record *t = NULL;
    uint32_t mask;

    mask = (depth == 0) ? DANETLS_EE_MASK : DANETLS_TA_MASK;

    /*
     * The trust store is not applicable with DANE-TA(2)
     */
    if (depth >= ctx->num_untrusted)
        mask &= DANETLS_PKIX_MASK;

    /*
     * If we've previously matched a PKIX-?? record, no need to test any
     * further PKIX-?? records, it remains to just build the PKIX chain.
     * Had the match been a DANE-?? record, we'd be done already.
     */
    if (dane->mdpth >= 0)
        mask &= ~DANETLS_PKIX_MASK;

    /*-
     * https://tools.ietf.org/html/rfc7671#section-5.1
     * https://tools.ietf.org/html/rfc7671#section-5.2
     * https://tools.ietf.org/html/rfc7671#section-5.3
     * https://tools.ietf.org/html/rfc7671#section-5.4
     *
     * We handle DANE-EE(3) records first as they require no chain building
     * and no expiration or hostname checks.  We also process digests with
     * higher ordinals first and ignore lower priorities except Full(0) which
     * is always processed (last).  If none match, we then process PKIX-EE(1).
     *
     * NOTE: This relies on DANE usages sorting before the corresponding PKIX
     * usages in SSL_dane_tlsa_add(), and also on descending sorting of digest
     * priorities.  See twin comment in ssl/ssl_lib.c.
     *
     * We expect that most TLSA RRsets will have just a single usage, so we
     * don't go out of our way to cache multiple selector-specific i2d buffers
     * across usages, but if the selector happens to remain the same as switch
     * usages, that's OK.  Thus, a set of "3 1 1", "3 0 1", "1 1 1", "1 0 1",
     * records would result in us generating each of the certificate and public
     * key DER forms twice, but more typically we'd just see multiple "3 1 1"
     * or multiple "3 0 1" records.
     *
     * As soon as we find a match at any given depth, we stop, because either
     * we've matched a DANE-?? record and the peer is authenticated, or, after
     * exhausting all DANE-?? records, we've matched a PKIX-?? record, which is
     * sufficient for DANE, and what remains to do is ordinary PKIX validation.
     */
    recnum = (dane->umask & mask) ? sk_danetls_record_num(dane->trecs) : 0;
    for (i = 0; matched == 0 && i < recnum; ++i) {
        t = sk_danetls_record_value(dane->trecs, i);
        if ((DANETLS_USAGE_BIT(t->usage) & mask) == 0)
            continue;
        if (t->usage != usage) {
            usage = t->usage;

            /* Reset digest agility for each usage/selector pair */
            mtype = DANETLS_NONE;
            ordinal = dane->dctx->mdord[t->mtype];
        }
        if (t->selector != selector) {
            selector = t->selector;

            /* Update per-selector state */
            OPENSSL_free(i2dbuf);
            i2dbuf = dane_i2d(cert, selector, &i2dlen);
            if (i2dbuf == NULL)
                return -1;

            /* Reset digest agility for each usage/selector pair */
            mtype = DANETLS_NONE;
            ordinal = dane->dctx->mdord[t->mtype];
        } else if (t->mtype != DANETLS_MATCHING_FULL) {
            /*-
             * Digest agility:
             *
             *     <https://tools.ietf.org/html/rfc7671#section-9>
             *
             * For a fixed selector, after processing all records with the
             * highest mtype ordinal, ignore all mtypes with lower ordinals
             * other than "Full".
             */
            if (dane->dctx->mdord[t->mtype] < ordinal)
                continue;
        }

        /*
         * Each time we hit a (new selector or) mtype, re-compute the relevant
         * digest, more complex caching is not worth the code space.
         */
        if (t->mtype != mtype) {
            const EVP_MD *md = dane->dctx->mdevp[mtype = t->mtype];
            cmpbuf = i2dbuf;
            cmplen = i2dlen;

            if (md != NULL) {
                cmpbuf = mdbuf;
                if (!EVP_Digest(i2dbuf, i2dlen, cmpbuf, &cmplen, md, 0)) {
                    matched = -1;
                    break;
                }
            }
        }

        /*
         * Squirrel away the certificate and depth if we have a match.  Any
         * DANE match is dispositive, but with PKIX we still need to build a
         * full chain.
         */
        if (cmplen == t->dlen &&
            memcmp(cmpbuf, t->data, cmplen) == 0) {
            if (DANETLS_USAGE_BIT(usage) & DANETLS_DANE_MASK)
                matched = 1;
            if (matched || dane->mdpth < 0) {
                dane->mdpth = depth;
                dane->mtlsa = t;
                OPENSSL_free(dane->mcert);
                dane->mcert = cert;
                X509_up_ref(cert);
            }
            break;
        }
    }

    /* Clear the one-element DER cache */
    OPENSSL_free(i2dbuf);
    return matched;
}