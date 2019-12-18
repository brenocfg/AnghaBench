#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scb {TYPE_2__* io_ctx; } ;
struct ahd_softc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpt_print_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
ahd_print_path(struct ahd_softc *ahd, struct scb *scb)
{
	xpt_print_path(scb->io_ctx->ccb_h.path);
}