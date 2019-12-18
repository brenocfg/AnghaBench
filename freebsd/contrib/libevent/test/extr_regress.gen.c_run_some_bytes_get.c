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
struct run {int some_bytes_set; int /*<<< orphan*/  some_bytes_length; int /*<<< orphan*/ * some_bytes_data; } ;
typedef  int /*<<< orphan*/  ev_uint8_t ;
typedef  int /*<<< orphan*/  ev_uint32_t ;

/* Variables and functions */

int
run_some_bytes_get(struct run *msg, ev_uint8_t * *value, ev_uint32_t *plen)
{
  if (msg->some_bytes_set != 1)
    return (-1);
  *value = msg->some_bytes_data;
  *plen = msg->some_bytes_length;
  return (0);
}