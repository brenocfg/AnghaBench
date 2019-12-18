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
struct TYPE_3__ {int /*<<< orphan*/ * tsa; } ;
typedef  TYPE_1__ TS_TST_INFO ;
typedef  int /*<<< orphan*/  GENERAL_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * GENERAL_NAME_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERAL_NAME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_F_TS_TST_INFO_SET_TSA ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int TS_TST_INFO_set_tsa(TS_TST_INFO *a, GENERAL_NAME *tsa)
{
    GENERAL_NAME *new_tsa;

    if (a->tsa == tsa)
        return 1;
    new_tsa = GENERAL_NAME_dup(tsa);
    if (new_tsa == NULL) {
        TSerr(TS_F_TS_TST_INFO_SET_TSA, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    GENERAL_NAME_free(a->tsa);
    a->tsa = new_tsa;
    return 1;
}