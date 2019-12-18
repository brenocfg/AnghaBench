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
typedef  int /*<<< orphan*/  NDEF_SUPPORT ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndef_prefix_free (int /*<<< orphan*/ *,unsigned char**,int*,void*) ; 

__attribute__((used)) static int ndef_suffix_free(BIO *b, unsigned char **pbuf, int *plen,
                            void *parg)
{
    NDEF_SUPPORT **pndef_aux = (NDEF_SUPPORT **)parg;
    if (!ndef_prefix_free(b, pbuf, plen, parg))
        return 0;
    OPENSSL_free(*pndef_aux);
    *pndef_aux = NULL;
    return 1;
}