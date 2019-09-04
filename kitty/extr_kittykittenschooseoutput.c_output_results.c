#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  len_t ;
struct TYPE_9__ {scalar_t__ score; } ;
struct TYPE_8__ {size_t limit; } ;
typedef  TYPE_1__ Options ;
typedef  int /*<<< orphan*/  GlobalData ;
typedef  TYPE_2__ Candidate ;

/* Variables and functions */
 int /*<<< orphan*/  cmpscore ; 
 int /*<<< orphan*/  output_result (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (TYPE_2__*,size_t,int,int /*<<< orphan*/ ) ; 

void
output_results(GlobalData *global, Candidate *haystack, size_t count, Options *opts, len_t needle_len) {
    Candidate *c;
    qsort(haystack, count, sizeof(*haystack), cmpscore);
    size_t left = opts->limit > 0 ? opts->limit : count;
    for (size_t i = 0; i < left; i++) {
        c = haystack + i;
        if (c->score > 0) output_result(global, c, opts, needle_len);
    }
}