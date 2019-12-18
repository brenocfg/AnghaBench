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
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* X509_NAME_oneline (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned long) ; 
 unsigned long XN_FLAG_COMPAT ; 
 unsigned long XN_FLAG_SEP_MASK ; 
 unsigned long XN_FLAG_SEP_MULTILINE ; 

void print_name(BIO *out, const char *title, X509_NAME *nm,
                unsigned long lflags)
{
    char *buf;
    char mline = 0;
    int indent = 0;

    if (title)
        BIO_puts(out, title);
    if ((lflags & XN_FLAG_SEP_MASK) == XN_FLAG_SEP_MULTILINE) {
        mline = 1;
        indent = 4;
    }
    if (lflags == XN_FLAG_COMPAT) {
        buf = X509_NAME_oneline(nm, 0, 0);
        BIO_puts(out, buf);
        BIO_puts(out, "\n");
        OPENSSL_free(buf);
    } else {
        if (mline)
            BIO_puts(out, "\n");
        X509_NAME_print_ex(out, nm, indent, lflags);
        BIO_puts(out, "\n");
    }
}