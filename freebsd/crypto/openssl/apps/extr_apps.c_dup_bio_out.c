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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_FP_TEXT ; 
 int BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * BIO_f_linebuffer () ; 
 int /*<<< orphan*/  BIO_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PREFIX_CTRL_SET_PREFIX ; 
 int /*<<< orphan*/ * apps_bf_prefix () ; 
 void* getenv (char*) ; 
 scalar_t__ istext (int) ; 
 int /*<<< orphan*/ * prefix_method ; 
 int /*<<< orphan*/  stdout ; 

BIO *dup_bio_out(int format)
{
    BIO *b = BIO_new_fp(stdout,
                        BIO_NOCLOSE | (istext(format) ? BIO_FP_TEXT : 0));
    void *prefix = NULL;

#ifdef OPENSSL_SYS_VMS
    if (istext(format))
        b = BIO_push(BIO_new(BIO_f_linebuffer()), b);
#endif

    if (istext(format) && (prefix = getenv("HARNESS_OSSL_PREFIX")) != NULL) {
        if (prefix_method == NULL)
            prefix_method = apps_bf_prefix();
        b = BIO_push(BIO_new(prefix_method), b);
        BIO_ctrl(b, PREFIX_CTRL_SET_PREFIX, 0, prefix);
    }

    return b;
}