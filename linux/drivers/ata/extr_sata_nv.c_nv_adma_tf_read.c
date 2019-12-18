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
struct ata_taskfile {int dummy; } ;
struct ata_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_sff_tf_read (struct ata_port*,struct ata_taskfile*) ; 
 int /*<<< orphan*/  nv_adma_register_mode (struct ata_port*) ; 

__attribute__((used)) static void nv_adma_tf_read(struct ata_port *ap, struct ata_taskfile *tf)
{
	/* Other than when internal or pass-through commands are executed,
	   the only time this function will be called in ADMA mode will be
	   if a command fails. In the failure case we don't care about going
	   into register mode with ADMA commands pending, as the commands will
	   all shortly be aborted anyway. We assume that NCQ commands are not
	   issued via passthrough, which is the only way that switching into
	   ADMA mode could abort outstanding commands. */
	nv_adma_register_mode(ap);

	ata_sff_tf_read(ap, tf);
}