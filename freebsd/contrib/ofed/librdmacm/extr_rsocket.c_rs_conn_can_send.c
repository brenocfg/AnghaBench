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
struct rsocket {int state; } ;

/* Variables and functions */
 scalar_t__ rs_can_send (struct rsocket*) ; 
 int rs_writable ; 

__attribute__((used)) static int rs_conn_can_send(struct rsocket *rs)
{
	return rs_can_send(rs) || !(rs->state & rs_writable);
}