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
struct ata_taskfile {int dummy; } ;
struct ata_port {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sff_exec_command ) (struct ata_port*,struct ata_taskfile const*) ;int /*<<< orphan*/  (* sff_tf_load ) (struct ata_port*,struct ata_taskfile const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ata_port*,struct ata_taskfile const*) ; 
 int /*<<< orphan*/  stub2 (struct ata_port*,struct ata_taskfile const*) ; 

__attribute__((used)) static inline void ata_tf_to_host(struct ata_port *ap,
				  const struct ata_taskfile *tf)
{
	ap->ops->sff_tf_load(ap, tf);
	ap->ops->sff_exec_command(ap, tf);
}