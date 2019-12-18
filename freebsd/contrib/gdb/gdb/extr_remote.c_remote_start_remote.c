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
struct ui_out {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_offsets () ; 
 int /*<<< orphan*/  immediate_quit ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 int /*<<< orphan*/  remote_current_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_desc ; 
 int remote_start_remote_dummy (struct ui_out*,void*) ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  set_thread (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
remote_start_remote (struct ui_out *uiout, void *dummy)
{
  immediate_quit++;		/* Allow user to interrupt it */

  /* Ack any packet which the remote side has already sent.  */
  serial_write (remote_desc, "+", 1);

  /* Let the stub know that we want it to return the thread.  */
  set_thread (-1, 0);

  inferior_ptid = remote_current_thread (inferior_ptid);

  get_offsets ();		/* Get text, data & bss offsets */

  putpkt ("?");			/* initiate a query from remote machine */
  immediate_quit--;

  /* NOTE: See comment above in remote_start_remote_dummy().  This
     function returns something >=0.  */
  return remote_start_remote_dummy (uiout, dummy);
}