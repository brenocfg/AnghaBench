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
struct TYPE_4__ {size_t len; } ;

/* Variables and functions */
 TYPE_1__ cur_resp ; 
 int /*<<< orphan*/  io_buffer_grow (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  io_buffer_tail (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void
send_data(const uint8_t *data, size_t len)
{

	io_buffer_grow(&cur_resp, len);
	memcpy(io_buffer_tail(&cur_resp), data, len);
	cur_resp.len += len;
}