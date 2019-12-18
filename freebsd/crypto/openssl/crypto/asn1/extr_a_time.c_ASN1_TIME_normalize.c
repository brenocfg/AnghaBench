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
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TIME_to_tm (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  V_ASN1_UNDEF ; 
 int /*<<< orphan*/ * asn1_time_from_tm (int /*<<< orphan*/ *,struct tm*,int /*<<< orphan*/ ) ; 

int ASN1_TIME_normalize(ASN1_TIME *t)
{
    struct tm tm;

    if (!ASN1_TIME_to_tm(t, &tm))
        return 0;

    return asn1_time_from_tm(t, &tm, V_ASN1_UNDEF) != NULL;
}