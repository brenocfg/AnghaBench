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
struct TYPE_3__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  cur_csum ; 
 TYPE_1__ cur_resp ; 
 int /*<<< orphan*/  debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_buffer_head (TYPE_1__*) ; 
 int /*<<< orphan*/  send_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_char (char) ; 

__attribute__((used)) static void
finish_packet(void)
{

	send_char('#');
	send_byte(cur_csum);
	debug("-> %.*s\n", (int)cur_resp.len, io_buffer_head(&cur_resp));
}