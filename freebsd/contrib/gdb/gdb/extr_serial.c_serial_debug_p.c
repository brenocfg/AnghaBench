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
struct serial {scalar_t__ debug_p; } ;

/* Variables and functions */
 scalar_t__ global_serial_debug_p ; 

int
serial_debug_p (struct serial *scb)
{
  return scb->debug_p || global_serial_debug_p;
}