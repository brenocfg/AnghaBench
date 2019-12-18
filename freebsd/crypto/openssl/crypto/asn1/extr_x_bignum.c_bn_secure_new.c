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
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 scalar_t__ BN_secure_new () ; 

__attribute__((used)) static int bn_secure_new(ASN1_VALUE **pval, const ASN1_ITEM *it)
{
    *pval = (ASN1_VALUE *)BN_secure_new();
    if (*pval != NULL)
        return 1;
    else
        return 0;
}