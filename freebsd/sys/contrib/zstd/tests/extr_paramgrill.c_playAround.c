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
typedef  int /*<<< orphan*/  winnerInfo_t ;
typedef  int /*<<< orphan*/  paramValues_t ;
typedef  int /*<<< orphan*/  contexts_t ;
struct TYPE_4__ {int /*<<< orphan*/  srcSize; } ;
typedef  TYPE_1__ buffers_t ;
typedef  int /*<<< orphan*/  UTIL_time_t ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_saveAndPrint_cLevelTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BMK_seed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const,int /*<<< orphan*/  const) ; 
 int FUZ_rand (int /*<<< orphan*/ *) ; 
 int* NB_TESTS_PLAYED (int /*<<< orphan*/ ) ; 
 scalar_t__ UTIL_clockSpanMicro (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  UTIL_getTime () ; 
 int /*<<< orphan*/  g_maxNbVariations ; 
 scalar_t__ g_maxVariationTime ; 
 int /*<<< orphan*/  g_rand ; 
 int /*<<< orphan*/  paramValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paramVaryOnce (int,int,int /*<<< orphan*/ *) ; 
 int strt_ind ; 

__attribute__((used)) static void playAround(FILE* f,
                       winnerInfo_t* winners,
                       paramValues_t p,
                       const buffers_t buf, const contexts_t ctx)
{
    int nbVariations = 0;
    UTIL_time_t const clockStart = UTIL_getTime();

    while (UTIL_clockSpanMicro(clockStart) < g_maxVariationTime) {
        if (nbVariations++ > g_maxNbVariations) break;

        do {
            int i;
            for(i = 0; i < 4; i++) {
                paramVaryOnce(FUZ_rand(&g_rand) % (strt_ind + 1),
                              ((FUZ_rand(&g_rand) & 1) << 1) - 1,
                              &p);
            }
        } while (!paramValid(p));

        /* exclude faster if already played params */
        if (FUZ_rand(&g_rand) & ((1 << *NB_TESTS_PLAYED(p))-1))
            continue;

        /* test */
        {   BYTE* const b = NB_TESTS_PLAYED(p);
            (*b)++;
        }
        if (!BMK_seed(winners, p, buf, ctx)) continue;

        /* improvement found => search more */
        BMK_saveAndPrint_cLevelTable(f, winners, buf.srcSize);
        playAround(f, winners, p, buf, ctx);
    }

}