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
struct qlnx_fastpath {int dummy; } ;
struct ecore_dev {int dummy; } ;
struct TYPE_4__ {int num_rss; struct qlnx_fastpath* fp_array; struct ecore_dev cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qlnx_free_mem_fp (TYPE_1__*,struct qlnx_fastpath*) ; 

__attribute__((used)) static void
qlnx_free_mem_load(qlnx_host_t *ha)
{
        int			i;
	struct ecore_dev	*cdev;

	cdev = &ha->cdev;

        for (i = 0; i < ha->num_rss; i++) {
                struct qlnx_fastpath *fp = &ha->fp_array[i];

                qlnx_free_mem_fp(ha, fp);
        }
	return;
}