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

/* Variables and functions */
 int /*<<< orphan*/  PEM_F_DO_B2I ; 
 int /*<<< orphan*/  PEM_R_KEYBLOB_HEADER_PARSE_ERROR ; 
 int /*<<< orphan*/  PEM_R_KEYBLOB_TOO_SHORT ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * b2i_dss (unsigned char const**,unsigned int,int) ; 
 int /*<<< orphan*/ * b2i_rsa (unsigned char const**,unsigned int,int) ; 
 unsigned int blob_length (unsigned int,int,int) ; 
 scalar_t__ do_blob_header (unsigned char const**,unsigned int,unsigned int*,unsigned int*,int*,int*) ; 

__attribute__((used)) static EVP_PKEY *do_b2i(const unsigned char **in, unsigned int length,
                        int ispub)
{
    const unsigned char *p = *in;
    unsigned int bitlen, magic;
    int isdss;
    if (do_blob_header(&p, length, &magic, &bitlen, &isdss, &ispub) <= 0) {
        PEMerr(PEM_F_DO_B2I, PEM_R_KEYBLOB_HEADER_PARSE_ERROR);
        return NULL;
    }
    length -= 16;
    if (length < blob_length(bitlen, isdss, ispub)) {
        PEMerr(PEM_F_DO_B2I, PEM_R_KEYBLOB_TOO_SHORT);
        return NULL;
    }
    if (isdss)
        return b2i_dss(&p, bitlen, ispub);
    else
        return b2i_rsa(&p, bitlen, ispub);
}