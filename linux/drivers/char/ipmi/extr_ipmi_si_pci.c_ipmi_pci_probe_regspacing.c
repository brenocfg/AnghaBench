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
struct si_sm_io {scalar_t__ si_type; int regspacing; unsigned char (* inputb ) (struct si_sm_io*,int) ;int /*<<< orphan*/  (* io_cleanup ) (struct si_sm_io*) ;int /*<<< orphan*/  (* outputb ) (struct si_sm_io*,int,int) ;int /*<<< orphan*/  dev; scalar_t__ (* io_setup ) (struct si_sm_io*) ;scalar_t__ regshift; int /*<<< orphan*/  regsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_REGSIZE ; 
 int DEFAULT_REGSPACING ; 
 scalar_t__ SI_KCS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (struct si_sm_io*) ; 
 int /*<<< orphan*/  stub2 (struct si_sm_io*,int,int) ; 
 unsigned char stub3 (struct si_sm_io*,int) ; 
 int /*<<< orphan*/  stub4 (struct si_sm_io*) ; 

__attribute__((used)) static int ipmi_pci_probe_regspacing(struct si_sm_io *io)
{
	if (io->si_type == SI_KCS) {
		unsigned char	status;
		int		regspacing;

		io->regsize = DEFAULT_REGSIZE;
		io->regshift = 0;

		/* detect 1, 4, 16byte spacing */
		for (regspacing = DEFAULT_REGSPACING; regspacing <= 16;) {
			io->regspacing = regspacing;
			if (io->io_setup(io)) {
				dev_err(io->dev, "Could not setup I/O space\n");
				return DEFAULT_REGSPACING;
			}
			/* write invalid cmd */
			io->outputb(io, 1, 0x10);
			/* read status back */
			status = io->inputb(io, 1);
			io->io_cleanup(io);
			if (status)
				return regspacing;
			regspacing *= 4;
		}
	}
	return DEFAULT_REGSPACING;
}