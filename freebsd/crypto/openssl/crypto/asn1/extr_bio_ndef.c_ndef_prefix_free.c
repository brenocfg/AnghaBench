#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * derbuf; } ;
typedef  TYPE_1__ NDEF_SUPPORT ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ndef_prefix_free(BIO *b, unsigned char **pbuf, int *plen,
                            void *parg)
{
    NDEF_SUPPORT *ndef_aux;

    if (!parg)
        return 0;

    ndef_aux = *(NDEF_SUPPORT **)parg;

    OPENSSL_free(ndef_aux->derbuf);

    ndef_aux->derbuf = NULL;
    *pbuf = NULL;
    *plen = 0;
    return 1;
}