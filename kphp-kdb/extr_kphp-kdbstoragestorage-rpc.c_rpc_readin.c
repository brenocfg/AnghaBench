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
struct connection {int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* packet_buffer ; 
 void* packet_end ; 
 void* packet_ptr ; 
 int read_in (int /*<<< orphan*/ *,void*,int) ; 

void rpc_readin (struct connection *c, int len) {
  assert (read_in (&c->In, packet_buffer, len) == len);
  packet_ptr = packet_buffer;
  packet_end = packet_buffer + (len >> 2);
}