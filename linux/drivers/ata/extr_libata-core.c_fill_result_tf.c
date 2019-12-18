#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ata_queued_cmd {TYPE_2__ tf; TYPE_1__ result_tf; struct ata_port* ap; } ;
struct ata_port {TYPE_3__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* qc_fill_rtf ) (struct ata_queued_cmd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ata_queued_cmd*) ; 

__attribute__((used)) static void fill_result_tf(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;

	qc->result_tf.flags = qc->tf.flags;
	ap->ops->qc_fill_rtf(qc);
}