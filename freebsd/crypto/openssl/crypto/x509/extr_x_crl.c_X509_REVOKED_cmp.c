#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  serialNumber; } ;
typedef  TYPE_1__ X509_REVOKED ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int ASN1_STRING_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int X509_REVOKED_cmp(const X509_REVOKED *const *a,
                            const X509_REVOKED *const *b)
{
    return (ASN1_STRING_cmp((ASN1_STRING *)&(*a)->serialNumber,
                            (ASN1_STRING *)&(*b)->serialNumber));
}