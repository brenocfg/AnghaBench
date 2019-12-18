#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ata_port_operations {int /*<<< orphan*/  postreset; int /*<<< orphan*/  softreset; int /*<<< orphan*/  prereset; int /*<<< orphan*/ * hardreset; } ;
struct ata_port {int /*<<< orphan*/  link; struct ata_port_operations* ops; } ;
typedef  int /*<<< orphan*/ * ata_reset_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ata_do_eh (struct ata_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sata_scr_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sata_std_hardreset ; 

void ata_std_error_handler(struct ata_port *ap)
{
	struct ata_port_operations *ops = ap->ops;
	ata_reset_fn_t hardreset = ops->hardreset;

	/* ignore built-in hardreset if SCR access is not available */
	if (hardreset == sata_std_hardreset && !sata_scr_valid(&ap->link))
		hardreset = NULL;

	ata_do_eh(ap, ops->prereset, ops->softreset, hardreset, ops->postreset);
}