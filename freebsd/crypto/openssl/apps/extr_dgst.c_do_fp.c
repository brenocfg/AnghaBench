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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_md_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 size_t BIO_gets (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ BIO_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char const*) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 size_t BUFSIZE ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestSignFinal (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 int EVP_DigestVerifyFinal (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/ * bio_err ; 

int do_fp(BIO *out, unsigned char *buf, BIO *bp, int sep, int binout,
          EVP_PKEY *key, unsigned char *sigin, int siglen,
          const char *sig_name, const char *md_name,
          const char *file)
{
    size_t len;
    int i;

    while (BIO_pending(bp) || !BIO_eof(bp)) {
        i = BIO_read(bp, (char *)buf, BUFSIZE);
        if (i < 0) {
            BIO_printf(bio_err, "Read Error in %s\n", file);
            ERR_print_errors(bio_err);
            return 1;
        }
        if (i == 0)
            break;
    }
    if (sigin != NULL) {
        EVP_MD_CTX *ctx;
        BIO_get_md_ctx(bp, &ctx);
        i = EVP_DigestVerifyFinal(ctx, sigin, (unsigned int)siglen);
        if (i > 0) {
            BIO_printf(out, "Verified OK\n");
        } else if (i == 0) {
            BIO_printf(out, "Verification Failure\n");
            return 1;
        } else {
            BIO_printf(bio_err, "Error Verifying Data\n");
            ERR_print_errors(bio_err);
            return 1;
        }
        return 0;
    }
    if (key != NULL) {
        EVP_MD_CTX *ctx;
        BIO_get_md_ctx(bp, &ctx);
        len = BUFSIZE;
        if (!EVP_DigestSignFinal(ctx, buf, &len)) {
            BIO_printf(bio_err, "Error Signing Data\n");
            ERR_print_errors(bio_err);
            return 1;
        }
    } else {
        len = BIO_gets(bp, (char *)buf, BUFSIZE);
        if ((int)len < 0) {
            ERR_print_errors(bio_err);
            return 1;
        }
    }

    if (binout) {
        BIO_write(out, buf, len);
    } else if (sep == 2) {
        for (i = 0; i < (int)len; i++)
            BIO_printf(out, "%02x", buf[i]);
        BIO_printf(out, " *%s\n", file);
    } else {
        if (sig_name != NULL) {
            BIO_puts(out, sig_name);
            if (md_name != NULL)
                BIO_printf(out, "-%s", md_name);
            BIO_printf(out, "(%s)= ", file);
        } else if (md_name != NULL) {
            BIO_printf(out, "%s(%s)= ", md_name, file);
        } else {
            BIO_printf(out, "(%s)= ", file);
        }
        for (i = 0; i < (int)len; i++) {
            if (sep && (i != 0))
                BIO_printf(out, ":");
            BIO_printf(out, "%02x", buf[i]);
        }
        BIO_printf(out, "\n");
    }
    return 0;
}