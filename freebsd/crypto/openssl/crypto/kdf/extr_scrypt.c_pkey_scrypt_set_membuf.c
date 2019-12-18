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
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  KDF_F_PKEY_SCRYPT_SET_MEMBUF ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 unsigned char* OPENSSL_memdup (unsigned char const*,int const) ; 

__attribute__((used)) static int pkey_scrypt_set_membuf(unsigned char **buffer, size_t *buflen,
                                  const unsigned char *new_buffer,
                                  const int new_buflen)
{
    if (new_buffer == NULL)
        return 1;

    if (new_buflen < 0)
        return 0;

    if (*buffer != NULL)
        OPENSSL_clear_free(*buffer, *buflen);

    if (new_buflen > 0) {
        *buffer = OPENSSL_memdup(new_buffer, new_buflen);
    } else {
        *buffer = OPENSSL_malloc(1);
    }
    if (*buffer == NULL) {
        KDFerr(KDF_F_PKEY_SCRYPT_SET_MEMBUF, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    *buflen = new_buflen;
    return 1;
}