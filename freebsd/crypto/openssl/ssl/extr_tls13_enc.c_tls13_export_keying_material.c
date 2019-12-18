#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  exporterlabel ;
struct TYPE_6__ {unsigned char* exporter_master_secret; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 scalar_t__ EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 scalar_t__ EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  ossl_statem_export_allowed (TYPE_1__*) ; 
 int /*<<< orphan*/ * ssl_handshake_md (TYPE_1__*) ; 
 int /*<<< orphan*/  tls13_hkdf_expand (TYPE_1__*,int /*<<< orphan*/  const*,unsigned char*,unsigned char const*,int,unsigned char*,unsigned int,unsigned char*,size_t,int /*<<< orphan*/ ) ; 

int tls13_export_keying_material(SSL *s, unsigned char *out, size_t olen,
                                 const char *label, size_t llen,
                                 const unsigned char *context,
                                 size_t contextlen, int use_context)
{
    unsigned char exportsecret[EVP_MAX_MD_SIZE];
#ifdef CHARSET_EBCDIC
    static const unsigned char exporterlabel[] = {0x65, 0x78, 0x70, 0x6F, 0x72, 0x74, 0x65, 0x72, 0x00};
#else
    static const unsigned char exporterlabel[] = "exporter";
#endif
    unsigned char hash[EVP_MAX_MD_SIZE], data[EVP_MAX_MD_SIZE];
    const EVP_MD *md = ssl_handshake_md(s);
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    unsigned int hashsize, datalen;
    int ret = 0;

    if (ctx == NULL || !ossl_statem_export_allowed(s))
        goto err;

    if (!use_context)
        contextlen = 0;

    if (EVP_DigestInit_ex(ctx, md, NULL) <= 0
            || EVP_DigestUpdate(ctx, context, contextlen) <= 0
            || EVP_DigestFinal_ex(ctx, hash, &hashsize) <= 0
            || EVP_DigestInit_ex(ctx, md, NULL) <= 0
            || EVP_DigestFinal_ex(ctx, data, &datalen) <= 0
            || !tls13_hkdf_expand(s, md, s->exporter_master_secret,
                                  (const unsigned char *)label, llen,
                                  data, datalen, exportsecret, hashsize, 0)
            || !tls13_hkdf_expand(s, md, exportsecret, exporterlabel,
                                  sizeof(exporterlabel) - 1, hash, hashsize,
                                  out, olen, 0))
        goto err;

    ret = 1;
 err:
    EVP_MD_CTX_free(ctx);
    return ret;
}