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
typedef  void* uint16_t ;
struct winsize {void* ws_row; void* ws_col; } ;
struct vtcon_port {struct tty* vtcport_tty; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct winsize*,int) ; 
 int /*<<< orphan*/  tty_set_winsize (struct tty*,struct winsize*) ; 

__attribute__((used)) static void
vtcon_port_change_size(struct vtcon_port *port, uint16_t cols, uint16_t rows)
{
	struct tty *tp;
	struct winsize sz;

	tp = port->vtcport_tty;

	if (tp == NULL)
		return;

	bzero(&sz, sizeof(struct winsize));
	sz.ws_col = cols;
	sz.ws_row = rows;

	tty_set_winsize(tp, &sz);
}