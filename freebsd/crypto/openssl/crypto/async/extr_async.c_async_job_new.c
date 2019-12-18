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
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ ASYNC_JOB ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_F_ASYNC_JOB_NEW ; 
 int /*<<< orphan*/  ASYNC_JOB_RUNNING ; 
 int /*<<< orphan*/  ASYNCerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static ASYNC_JOB *async_job_new(void)
{
    ASYNC_JOB *job = NULL;

    job = OPENSSL_zalloc(sizeof(*job));
    if (job == NULL) {
        ASYNCerr(ASYNC_F_ASYNC_JOB_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    job->status = ASYNC_JOB_RUNNING;

    return job;
}