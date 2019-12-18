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
 int BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  X509_F_X509_NAME_PRINT ; 
 char* X509_NAME_oneline (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ossl_isupper (char) ; 

int X509_NAME_print(BIO *bp, const X509_NAME *name, int obase)
{
    char *s, *c, *b;
    int l, i;

    l = 80 - 2 - obase;

    b = X509_NAME_oneline(name, NULL, 0);
    if (!b)
        return 0;
    if (!*b) {
        OPENSSL_free(b);
        return 1;
    }
    s = b + 1;                  /* skip the first slash */

    c = s;
    for (;;) {
        if (((*s == '/') &&
             (ossl_isupper(s[1]) && ((s[2] == '=') ||
                                (ossl_isupper(s[2]) && (s[3] == '='))
              ))) || (*s == '\0'))
        {
            i = s - c;
            if (BIO_write(bp, c, i) != i)
                goto err;
            c = s + 1;          /* skip following slash */
            if (*s != '\0') {
                if (BIO_write(bp, ", ", 2) != 2)
                    goto err;
            }
            l--;
        }
        if (*s == '\0')
            break;
        s++;
        l--;
    }

    OPENSSL_free(b);
    return 1;
 err:
    X509err(X509_F_X509_NAME_PRINT, ERR_R_BUF_LIB);
    OPENSSL_free(b);
    return 0;
}