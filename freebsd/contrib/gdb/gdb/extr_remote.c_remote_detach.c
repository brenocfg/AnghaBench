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
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;

/* Variables and functions */
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 
 int /*<<< orphan*/  remote_desc ; 
 int /*<<< orphan*/  remote_send (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ target_is_async_p () ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 

__attribute__((used)) static void
remote_detach (char *args, int from_tty)
{
  struct remote_state *rs = get_remote_state ();
  char *buf = alloca (rs->remote_packet_size);

  if (args)
    error ("Argument given to \"detach\" when remotely debugging.");

  /* Tell the remote target to detach.  */
  strcpy (buf, "D");
  remote_send (buf, (rs->remote_packet_size));

  /* Unregister the file descriptor from the event loop. */
  if (target_is_async_p ())
    serial_async (remote_desc, NULL, 0);

  target_mourn_inferior ();
  if (from_tty)
    puts_filtered ("Ending remote debugging.\n");
}