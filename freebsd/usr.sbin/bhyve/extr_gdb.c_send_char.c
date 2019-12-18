#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 TYPE_1__ cur_resp ; 
 int /*<<< orphan*/  io_buffer_grow (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * io_buffer_tail (TYPE_1__*) ; 

__attribute__((used)) static void
send_char(uint8_t data)
{
	io_buffer_grow(&cur_resp, 1);
	*io_buffer_tail(&cur_resp) = data;
	cur_resp.len++;
}