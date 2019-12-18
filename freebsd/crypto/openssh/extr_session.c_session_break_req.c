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
struct TYPE_3__ {int ptymaster; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  packet_check_eom () ; 
 int /*<<< orphan*/  packet_get_int () ; 
 scalar_t__ tcsendbreak (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
session_break_req(struct ssh *ssh, Session *s)
{

	packet_get_int();	/* ignored */
	packet_check_eom();

	if (s->ptymaster == -1 || tcsendbreak(s->ptymaster, 0) < 0)
		return 0;
	return 1;
}