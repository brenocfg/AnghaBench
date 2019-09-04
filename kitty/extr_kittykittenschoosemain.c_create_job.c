#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t haystack_count; TYPE_1__* haystack; } ;
struct TYPE_9__ {size_t start; size_t count; TYPE_3__* global; int /*<<< orphan*/  workspace; scalar_t__ max_haystack_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  haystack_len; } ;
typedef  TYPE_2__ JobData ;
typedef  TYPE_3__ GlobalData ;

/* Variables and functions */
 scalar_t__ MAX (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_workspace (scalar_t__,TYPE_3__*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static JobData*
create_job(size_t i, size_t blocksz, GlobalData *global) {
    JobData *ans = (JobData*)calloc(1, sizeof(JobData));
    if (ans == NULL) return NULL;
    ans->start = i * blocksz;
    if (ans->start >= global->haystack_count) ans->count = 0;
    else ans->count = global->haystack_count - ans->start;
    ans->max_haystack_len = 0;
    for (size_t i = ans->start; i < ans->start + ans->count; i++) ans->max_haystack_len = MAX(ans->max_haystack_len, global->haystack[i].haystack_len);
    if (ans->count > 0) {
        ans->workspace = alloc_workspace(ans->max_haystack_len, global);
        if (!ans->workspace) { free(ans); return NULL; }
    }
    ans->global = global;
    return ans;
}