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
typedef  int /*<<< orphan*/  winnerInfo_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_print_cLevelTable (int /*<<< orphan*/ * const,int /*<<< orphan*/  const*,size_t const) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * const stdout ; 

__attribute__((used)) static void
BMK_saveAndPrint_cLevelTable(FILE* const f,
                       const winnerInfo_t* winners,
                       const size_t srcSize)
{
    fseek(f, 0, SEEK_SET);
    BMK_print_cLevelTable(f, winners, srcSize);
    fflush(f);
    BMK_print_cLevelTable(stdout, winners, srcSize);
}