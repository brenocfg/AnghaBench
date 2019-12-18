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
typedef  union ctl_io {int dummy; } ctl_io ;
struct ctl_be_block_io {int /*<<< orphan*/  (* beio_cont ) (struct ctl_be_block_io*) ;union ctl_io* io; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctl_data_submit_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_free_beio (struct ctl_be_block_io*) ; 
 int /*<<< orphan*/  stub1 (struct ctl_be_block_io*) ; 

__attribute__((used)) static void
ctl_complete_beio(struct ctl_be_block_io *beio)
{
	union ctl_io *io = beio->io;

	if (beio->beio_cont != NULL) {
		beio->beio_cont(beio);
	} else {
		ctl_free_beio(beio);
		ctl_data_submit_done(io);
	}
}