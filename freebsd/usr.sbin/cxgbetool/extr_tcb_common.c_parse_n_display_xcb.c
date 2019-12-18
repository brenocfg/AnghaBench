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

/* Variables and functions */
 scalar_t__ g_got_fcb ; 
 scalar_t__ g_got_scb ; 
 int /*<<< orphan*/  parse_n_display_fcb (unsigned char*) ; 
 int /*<<< orphan*/  parse_n_display_scb (unsigned char*) ; 
 int /*<<< orphan*/  parse_n_display_tcb (unsigned char*) ; 

void
parse_n_display_xcb(unsigned char *buf)
{
  if      (g_got_scb) parse_n_display_scb(buf);
  else if (g_got_fcb) parse_n_display_fcb(buf);
  else                parse_n_display_tcb(buf);
}