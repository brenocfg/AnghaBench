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
struct tm {int dummy; } ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ ASN1_UTCTIME ;

/* Variables and functions */
 scalar_t__ V_ASN1_UTCTIME ; 
 int asn1_time_to_tm (struct tm*,TYPE_1__ const*) ; 

int asn1_utctime_to_tm(struct tm *tm, const ASN1_UTCTIME *d)
{
    /* wrapper around ans1_time_to_tm */
    if (d->type != V_ASN1_UTCTIME)
        return 0;
    return asn1_time_to_tm(tm, d);
}