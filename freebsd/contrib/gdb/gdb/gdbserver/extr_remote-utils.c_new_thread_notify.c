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
 int /*<<< orphan*/  disable_async_io () ; 
 int /*<<< orphan*/  enable_async_io () ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 scalar_t__ server_waiting ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
new_thread_notify (int id)
{
  char own_buf[256];

  /* The `n' response is not yet part of the remote protocol.  Do nothing.  */
  if (1)
    return;

  if (server_waiting == 0)
    return;

  sprintf (own_buf, "n%x", id);
  disable_async_io ();
  putpkt (own_buf);
  enable_async_io ();
}