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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_TYPE_CIPHER ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_cipher_status (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_method_type (int /*<<< orphan*/ *) ; 
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int BIO_write (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  CMS_F_CMS_COPY_CONTENT ; 
 int /*<<< orphan*/  CMS_R_SMIME_TEXT_ERROR ; 
 unsigned int CMS_TEXT ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  SMIME_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cms_get_text_bio (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int cms_copy_content(BIO *out, BIO *in, unsigned int flags)
{
    unsigned char buf[4096];
    int r = 0, i;
    BIO *tmpout;

    tmpout = cms_get_text_bio(out, flags);

    if (tmpout == NULL) {
        CMSerr(CMS_F_CMS_COPY_CONTENT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* Read all content through chain to process digest, decrypt etc */
    for (;;) {
        i = BIO_read(in, buf, sizeof(buf));
        if (i <= 0) {
            if (BIO_method_type(in) == BIO_TYPE_CIPHER) {
                if (!BIO_get_cipher_status(in))
                    goto err;
            }
            if (i < 0)
                goto err;
            break;
        }

        if (tmpout && (BIO_write(tmpout, buf, i) != i))
            goto err;
    }

    if (flags & CMS_TEXT) {
        if (!SMIME_text(tmpout, out)) {
            CMSerr(CMS_F_CMS_COPY_CONTENT, CMS_R_SMIME_TEXT_ERROR);
            goto err;
        }
    }

    r = 1;

 err:
    if (tmpout != out)
        BIO_free(tmpout);
    return r;

}