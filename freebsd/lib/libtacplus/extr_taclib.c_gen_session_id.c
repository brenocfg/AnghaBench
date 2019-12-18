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
struct tac_msg {int* session_id; } ;

/* Variables and functions */
 int random () ; 

__attribute__((used)) static void
gen_session_id(struct tac_msg *msg)
{
	int r;

	r = random();
	msg->session_id[0] = r >> 8;
	msg->session_id[1] = r;
	r = random();
	msg->session_id[2] = r >> 8;
	msg->session_id[3] = r;
}