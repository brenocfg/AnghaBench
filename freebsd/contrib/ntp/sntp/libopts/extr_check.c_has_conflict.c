#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pzProgName; TYPE_2__* pOptDesc; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_8__ {int* pOptMust; int* pOptCant; int /*<<< orphan*/  pz_Name; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 int const NO_EQUIVALENT ; 
 scalar_t__ SELECTED_OPT (TYPE_2__*) ; 
 scalar_t__ UNUSED_OPT (TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* zconflict_fmt ; 
 char* zneed_fmt ; 

__attribute__((used)) static bool
has_conflict(tOptions * pOpts, tOptDesc * od)
{
    if (od->pOptMust != NULL) {
        int const * must = od->pOptMust;

        while (*must != NO_EQUIVALENT) {
            tOptDesc * p = pOpts->pOptDesc + *(must++);
            if (UNUSED_OPT(p)) {
                const tOptDesc * ood = pOpts->pOptDesc + must[-1];
                fprintf(stderr, zneed_fmt, pOpts->pzProgName,
                        od->pz_Name, ood->pz_Name);
                return true;
            }
        }
    }

    if (od->pOptCant != NULL) {
        int const * cant = od->pOptCant;

        while (*cant != NO_EQUIVALENT) {
            tOptDesc * p = pOpts->pOptDesc + *(cant++);
            if (SELECTED_OPT(p)) {
                const tOptDesc * ood = pOpts->pOptDesc + cant[-1];
                fprintf(stderr, zconflict_fmt, pOpts->pzProgName,
                        od->pz_Name, ood->pz_Name);
                return true;
            }
        }
    }

    return false;
}