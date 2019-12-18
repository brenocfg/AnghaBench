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
typedef  int /*<<< orphan*/  e_salt ;
typedef  int /*<<< orphan*/  e_buf ;

/* Variables and functions */
 char* DES_fcrypt (char const*,char const*,char*) ; 
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  ascii2ebcdic (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebcdic2ascii (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

char *DES_crypt(const char *buf, const char *salt)
{
    static char buff[14];

#ifndef CHARSET_EBCDIC
    return DES_fcrypt(buf, salt, buff);
#else
    char e_salt[2 + 1];
    char e_buf[32 + 1];         /* replace 32 by 8 ? */
    char *ret;

    if (salt[0] == '\0' || salt[1] == '\0')
        return NULL;

    /* Copy salt, convert to ASCII. */
    e_salt[0] = salt[0];
    e_salt[1] = salt[1];
    e_salt[2] = '\0';
    ebcdic2ascii(e_salt, e_salt, sizeof(e_salt));

    /* Convert password to ASCII. */
    OPENSSL_strlcpy(e_buf, buf, sizeof(e_buf));
    ebcdic2ascii(e_buf, e_buf, sizeof(e_buf));

    /* Encrypt it (from/to ASCII); if it worked, convert back. */
    ret = DES_fcrypt(e_buf, e_salt, buff);
    if (ret != NULL)
        ascii2ebcdic(ret, ret, strlen(ret));

    return ret;
#endif
}