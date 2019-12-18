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

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_OPENSSL_BUF2HEXSTR ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 char* OPENSSL_malloc (long) ; 
 char* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  ebcdic2ascii (char*,char*,int) ; 

char *OPENSSL_buf2hexstr(const unsigned char *buffer, long len)
{
    static const char hexdig[] = "0123456789ABCDEF";
    char *tmp, *q;
    const unsigned char *p;
    int i;

    if (len == 0)
    {
        return OPENSSL_zalloc(1);
    }

    if ((tmp = OPENSSL_malloc(len * 3)) == NULL) {
        CRYPTOerr(CRYPTO_F_OPENSSL_BUF2HEXSTR, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    q = tmp;
    for (i = 0, p = buffer; i < len; i++, p++) {
        *q++ = hexdig[(*p >> 4) & 0xf];
        *q++ = hexdig[*p & 0xf];
        *q++ = ':';
    }
    q[-1] = 0;
#ifdef CHARSET_EBCDIC
    ebcdic2ascii(tmp, tmp, q - tmp - 1);
#endif

    return tmp;
}