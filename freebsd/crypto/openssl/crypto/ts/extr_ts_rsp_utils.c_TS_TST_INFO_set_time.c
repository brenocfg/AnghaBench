#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  const* time; } ;
typedef  TYPE_1__ TS_TST_INFO ;
typedef  int /*<<< orphan*/  const ASN1_GENERALIZEDTIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ASN1_STRING_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  TS_F_TS_TST_INFO_SET_TIME ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int TS_TST_INFO_set_time(TS_TST_INFO *a, const ASN1_GENERALIZEDTIME *gtime)
{
    ASN1_GENERALIZEDTIME *new_time;

    if (a->time == gtime)
        return 1;
    new_time = ASN1_STRING_dup(gtime);
    if (new_time == NULL) {
        TSerr(TS_F_TS_TST_INFO_SET_TIME, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    ASN1_GENERALIZEDTIME_free(a->time);
    a->time = new_time;
    return 1;
}