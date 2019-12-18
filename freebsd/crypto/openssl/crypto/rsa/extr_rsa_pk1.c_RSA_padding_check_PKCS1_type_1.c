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
 int /*<<< orphan*/  RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1 ; 
 int /*<<< orphan*/  RSA_R_BAD_FIXED_HEADER_DECRYPT ; 
 int /*<<< orphan*/  RSA_R_BAD_PAD_BYTE_COUNT ; 
 int /*<<< orphan*/  RSA_R_BLOCK_TYPE_IS_NOT_01 ; 
 int /*<<< orphan*/  RSA_R_DATA_TOO_LARGE ; 
 int /*<<< orphan*/  RSA_R_INVALID_PADDING ; 
 int /*<<< orphan*/  RSA_R_NULL_BEFORE_BLOCK_MISSING ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned int) ; 

int RSA_padding_check_PKCS1_type_1(unsigned char *to, int tlen,
                                   const unsigned char *from, int flen,
                                   int num)
{
    int i, j;
    const unsigned char *p;

    p = from;

    /*
     * The format is
     * 00 || 01 || PS || 00 || D
     * PS - padding string, at least 8 bytes of FF
     * D  - data.
     */

    if (num < 11)
        return -1;

    /* Accept inputs with and without the leading 0-byte. */
    if (num == flen) {
        if ((*p++) != 0x00) {
            RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,
                   RSA_R_INVALID_PADDING);
            return -1;
        }
        flen--;
    }

    if ((num != (flen + 1)) || (*(p++) != 0x01)) {
        RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,
               RSA_R_BLOCK_TYPE_IS_NOT_01);
        return -1;
    }

    /* scan over padding data */
    j = flen - 1;               /* one for type. */
    for (i = 0; i < j; i++) {
        if (*p != 0xff) {       /* should decrypt to 0xff */
            if (*p == 0) {
                p++;
                break;
            } else {
                RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,
                       RSA_R_BAD_FIXED_HEADER_DECRYPT);
                return -1;
            }
        }
        p++;
    }

    if (i == j) {
        RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,
               RSA_R_NULL_BEFORE_BLOCK_MISSING);
        return -1;
    }

    if (i < 8) {
        RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,
               RSA_R_BAD_PAD_BYTE_COUNT);
        return -1;
    }
    i++;                        /* Skip over the '\0' */
    j -= i;
    if (j > tlen) {
        RSAerr(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1, RSA_R_DATA_TOO_LARGE);
        return -1;
    }
    memcpy(to, p, (unsigned int)j);

    return j;
}