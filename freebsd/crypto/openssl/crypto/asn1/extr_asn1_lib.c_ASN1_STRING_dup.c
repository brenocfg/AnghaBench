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
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_STRING_new () ; 

ASN1_STRING *ASN1_STRING_dup(const ASN1_STRING *str)
{
    ASN1_STRING *ret;
    if (!str)
        return NULL;
    ret = ASN1_STRING_new();
    if (ret == NULL)
        return NULL;
    if (!ASN1_STRING_copy(ret, str)) {
        ASN1_STRING_free(ret);
        return NULL;
    }
    return ret;
}