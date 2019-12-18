#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ ASN1_TIME ;

/* Variables and functions */
 int ASN1_GENERALIZEDTIME_check (TYPE_1__ const*) ; 
 int ASN1_UTCTIME_check (TYPE_1__ const*) ; 
 scalar_t__ V_ASN1_GENERALIZEDTIME ; 
 scalar_t__ V_ASN1_UTCTIME ; 

int ASN1_TIME_check(const ASN1_TIME *t)
{
    if (t->type == V_ASN1_GENERALIZEDTIME)
        return ASN1_GENERALIZEDTIME_check(t);
    else if (t->type == V_ASN1_UTCTIME)
        return ASN1_UTCTIME_check(t);
    return 0;
}