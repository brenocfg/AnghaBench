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
struct TYPE_4__ {int num_rss; struct qlnx_fastpath* fp_array; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int qlnx_alloc_mem_fp (TYPE_1__*,struct qlnx_fastpath*) ; 

__attribute__((used)) static int
qlnx_alloc_mem_load(qlnx_host_t *ha)
{
        int	rc = 0, rss_id;

        for (rss_id = 0; rss_id < ha->num_rss; rss_id++) {
                struct qlnx_fastpath *fp = &ha->fp_array[rss_id];

                rc = qlnx_alloc_mem_fp(ha, fp);
                if (rc)
                        break;
        }
	return (rc);
}