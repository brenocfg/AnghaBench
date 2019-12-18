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
struct filed {int f_file; int f_type; int /*<<< orphan*/  fu_pipe_pid; int /*<<< orphan*/ * fu_forw_addr; } ;

/* Variables and functions */
#define  F_CONSOLE 132 
#define  F_FILE 131 
#define  F_FORW 130 
#define  F_PIPE 129 
#define  F_TTY 128 
 int F_UNUSED ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  freeaddrinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
close_filed(struct filed *f)
{

	if (f == NULL || f->f_file == -1)
		return;

	switch (f->f_type) {
	case F_FORW:
		if (f->fu_forw_addr != NULL) {
			freeaddrinfo(f->fu_forw_addr);
			f->fu_forw_addr = NULL;
		}
		/* FALLTHROUGH */

	case F_FILE:
	case F_TTY:
	case F_CONSOLE:
		f->f_type = F_UNUSED;
		break;
	case F_PIPE:
		f->fu_pipe_pid = 0;
		break;
	}
	(void)close(f->f_file);
	f->f_file = -1;
}