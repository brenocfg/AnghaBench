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
struct TYPE_4__ {int /*<<< orphan*/  fibrectx; struct TYPE_4__* funcargs; } ;
typedef  TYPE_1__ ASYNC_JOB ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  async_fibre_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void async_job_free(ASYNC_JOB *job)
{
    if (job != NULL) {
        OPENSSL_free(job->funcargs);
        async_fibre_free(&job->fibrectx);
        OPENSSL_free(job);
    }
}