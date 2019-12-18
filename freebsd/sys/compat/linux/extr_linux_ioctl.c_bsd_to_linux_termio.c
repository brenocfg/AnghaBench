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
struct termios {int dummy; } ;
struct linux_termios {int /*<<< orphan*/  c_cc; int /*<<< orphan*/  c_line; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_cflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; } ;
struct linux_termio {int /*<<< orphan*/  c_cc; int /*<<< orphan*/  c_line; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_cflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_NCC ; 
 int /*<<< orphan*/  bsd_to_linux_termios (struct termios*,struct linux_termios*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct linux_termio*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bsd_to_linux_termio(struct termios *bios, struct linux_termio *lio)
{
	struct linux_termios lios;

	memset(lio, 0, sizeof(*lio));
	bsd_to_linux_termios(bios, &lios);
	lio->c_iflag = lios.c_iflag;
	lio->c_oflag = lios.c_oflag;
	lio->c_cflag = lios.c_cflag;
	lio->c_lflag = lios.c_lflag;
	lio->c_line  = lios.c_line;
	memcpy(lio->c_cc, lios.c_cc, LINUX_NCC);
}