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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  PKCS7_RECIP_INFO ;
typedef  int /*<<< orphan*/  PKCS7 ;

/* Variables and functions */
 int /*<<< orphan*/  PKCS7_RECIP_INFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS7_RECIP_INFO_new () ; 
 int /*<<< orphan*/  PKCS7_RECIP_INFO_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7_add_recipient_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

PKCS7_RECIP_INFO *PKCS7_add_recipient(PKCS7 *p7, X509 *x509)
{
    PKCS7_RECIP_INFO *ri;

    if ((ri = PKCS7_RECIP_INFO_new()) == NULL)
        goto err;
    if (!PKCS7_RECIP_INFO_set(ri, x509))
        goto err;
    if (!PKCS7_add_recipient_info(p7, ri))
        goto err;
    return ri;
 err:
    PKCS7_RECIP_INFO_free(ri);
    return NULL;
}