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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  ASN1_ENUMERATED ;

/* Variables and functions */
 int /*<<< orphan*/  V_ASN1_ENUMERATED ; 
 int asn1_string_get_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int ASN1_ENUMERATED_get_int64(int64_t *pr, const ASN1_ENUMERATED *a)
{
    return asn1_string_get_int64(pr, a, V_ASN1_ENUMERATED);
}