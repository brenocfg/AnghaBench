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
struct TYPE_3__ {int /*<<< orphan*/  const* seconds; } ;
typedef  TYPE_1__ TS_ACCURACY ;
typedef  int /*<<< orphan*/  const ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  const* ASN1_INTEGER_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  TS_F_TS_ACCURACY_SET_SECONDS ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int TS_ACCURACY_set_seconds(TS_ACCURACY *a, const ASN1_INTEGER *seconds)
{
    ASN1_INTEGER *new_seconds;

    if (a->seconds == seconds)
        return 1;
    new_seconds = ASN1_INTEGER_dup(seconds);
    if (new_seconds == NULL) {
        TSerr(TS_F_TS_ACCURACY_SET_SECONDS, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    ASN1_INTEGER_free(a->seconds);
    a->seconds = new_seconds;
    return 1;
}