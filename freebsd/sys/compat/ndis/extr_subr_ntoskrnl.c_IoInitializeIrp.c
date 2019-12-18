#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/ * irp_csl; } ;
struct TYPE_6__ {TYPE_1__ irp_overlay; } ;
struct TYPE_7__ {int irp_stackcnt; int irp_currentstackloc; TYPE_2__ irp_tail; int /*<<< orphan*/  irp_thlist; int /*<<< orphan*/  irp_size; } ;
typedef  TYPE_3__ irp ;
typedef  int /*<<< orphan*/  io_stack_location ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoSizeOfIrp (int) ; 
 int /*<<< orphan*/  bzero (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
IoInitializeIrp(irp *io, uint16_t psize, uint8_t ssize)
{
	bzero((char *)io, IoSizeOfIrp(ssize));
	io->irp_size = psize;
	io->irp_stackcnt = ssize;
	io->irp_currentstackloc = ssize;
	InitializeListHead(&io->irp_thlist);
	io->irp_tail.irp_overlay.irp_csl =
	    (io_stack_location *)(io + 1) + ssize;
}