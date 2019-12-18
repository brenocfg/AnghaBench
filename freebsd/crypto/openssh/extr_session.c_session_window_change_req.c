#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_3__ {void* ypixel; void* xpixel; void* col; void* row; int /*<<< orphan*/  ptyfd; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  packet_check_eom () ; 
 void* packet_get_int () ; 
 int /*<<< orphan*/  pty_change_window_size (int /*<<< orphan*/ ,void*,void*,void*,void*) ; 

__attribute__((used)) static int
session_window_change_req(struct ssh *ssh, Session *s)
{
	s->col = packet_get_int();
	s->row = packet_get_int();
	s->xpixel = packet_get_int();
	s->ypixel = packet_get_int();
	packet_check_eom();
	pty_change_window_size(s->ptyfd, s->row, s->col, s->xpixel, s->ypixel);
	return 1;
}