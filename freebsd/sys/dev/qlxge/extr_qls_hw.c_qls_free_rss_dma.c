#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ rss_dma; } ;
struct TYPE_6__ {TYPE_1__ flags; int /*<<< orphan*/  rss_dma; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qls_free_dmabuf (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qls_free_rss_dma(qla_host_t *ha)
{
	qls_free_dmabuf(ha, &ha->rss_dma);
	ha->flags.rss_dma = 0;
}