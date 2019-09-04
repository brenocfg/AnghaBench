#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int haystack_size; size_t haystack_count; } ;
struct TYPE_12__ {int started; scalar_t__ count; } ;
typedef  TYPE_1__ JobData ;
typedef  TYPE_2__ GlobalData ;

/* Variables and functions */
 size_t MAX (int,int) ; 
 int /*<<< orphan*/  START_FUNC ; 
 void* alloc_threads (size_t) ; 
 TYPE_1__** calloc (size_t,int) ; 
 int cpu_count () ; 
 TYPE_1__* create_job (size_t,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 TYPE_1__* free_job (TYPE_1__*) ; 
 int /*<<< orphan*/  free_threads (void*) ; 
 int /*<<< orphan*/  run_scoring (TYPE_1__*) ; 
 int /*<<< orphan*/  start_thread (void*,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  wait_for_thread (void*,size_t) ; 

__attribute__((used)) static int
run_threaded(int num_threads_asked, GlobalData *global) {
    int ret = 0;
    size_t i, blocksz;
    size_t num_threads = MAX(1, num_threads_asked > 0 ? num_threads_asked : cpu_count());
    if (global->haystack_size < 10000) num_threads = 1;
    /* printf("num_threads: %lu asked: %d sysconf: %ld\n", num_threads, num_threads_asked, sysconf(_SC_NPROCESSORS_ONLN)); */

    void *threads = alloc_threads(num_threads);
    JobData **job_data = calloc(num_threads, sizeof(JobData*));
    if (threads == NULL || job_data == NULL) { ret = 1; goto end; }

    blocksz = global->haystack_count / num_threads + global->haystack_count % num_threads;

    for (i = 0; i < num_threads; i++) {
        job_data[i] = create_job(i, blocksz, global);
        if (job_data[i] == NULL) { ret = 1; goto end; }
    }

    if (num_threads == 1) {
        run_scoring(job_data[0]);
    } else {
        for (i = 0; i < num_threads; i++) {
            job_data[i]->started = false;
            if (job_data[i]->count > 0) {
                if (!start_thread(threads, i, START_FUNC, job_data[i])) ret = 1;
                else job_data[i]->started = true;
            }
        }
    }

end:
    if (num_threads > 1 && job_data) {
        for (i = 0; i < num_threads; i++) {
            if (job_data[i] && job_data[i]->started) wait_for_thread(threads, i);
        }
    }
    for (i = 0; i < num_threads; i++) job_data[i] = free_job(job_data[i]);
    free(job_data);
    free_threads(threads);
    return ret;
}