#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cvmx_shmem_dscptr {int dummy; } ;
struct TYPE_2__ {struct cvmx_shmem_dscptr* shmd; } ;

/* Variables and functions */
 int CVMX_SHMEM_NUM_DSCPTR ; 
 int /*<<< orphan*/  __CHECK_APP_SMDR ; 
 TYPE_1__* __smdr ; 
 struct cvmx_shmem_dscptr* stub1 (struct cvmx_shmem_dscptr*,void*) ; 

__attribute__((used)) static struct cvmx_shmem_dscptr *__smdr_iterator(struct cvmx_shmem_dscptr *(*f)(struct cvmx_shmem_dscptr *dscptr, void *p), void *param )
{
    struct cvmx_shmem_dscptr *d, *dscptr = NULL;
    int i;

    __CHECK_APP_SMDR;

    for (i = 0; i < CVMX_SHMEM_NUM_DSCPTR; i++)
    {
        d = &__smdr->shmd[i];
        if ((dscptr = (*f)(d, param)) != NULL)
            break;      /* stop iteration */
    }

   return dscptr;
}