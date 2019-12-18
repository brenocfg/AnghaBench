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
typedef  int /*<<< orphan*/  point_conversion_form_t ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 size_t EC_POINT_point2buf (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *) ; 
 void** HEX_DIGITS ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 char* OPENSSL_malloc (size_t) ; 

char *EC_POINT_point2hex(const EC_GROUP *group,
                         const EC_POINT *point,
                         point_conversion_form_t form, BN_CTX *ctx)
{
    char *ret, *p;
    size_t buf_len = 0, i;
    unsigned char *buf = NULL, *pbuf;

    buf_len = EC_POINT_point2buf(group, point, form, &buf, ctx);

    if (buf_len == 0)
        return NULL;

    ret = OPENSSL_malloc(buf_len * 2 + 2);
    if (ret == NULL) {
        OPENSSL_free(buf);
        return NULL;
    }
    p = ret;
    pbuf = buf;
    for (i = buf_len; i > 0; i--) {
        int v = (int)*(pbuf++);
        *(p++) = HEX_DIGITS[v >> 4];
        *(p++) = HEX_DIGITS[v & 0x0F];
    }
    *p = '\0';

    OPENSSL_free(buf);

    return ret;
}