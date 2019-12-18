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
struct target_ops {int dummy; } ;
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC_NULL_PID ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  SOLIB_CREATE_INFERIOR_HOOK (int /*<<< orphan*/ ) ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 int baud_rate ; 
 int catch_exceptions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int continue_thread ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ exec_bfd ; 
 int general_thread ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_all_packet_configs () ; 
 int /*<<< orphan*/  no_shared_libraries (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  pid_to_ptid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_target () ; 
 int /*<<< orphan*/  push_target (struct target_ops*) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 
 int remote_async_terminal_ours_p ; 
 int /*<<< orphan*/  remote_check_symbols (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * remote_desc ; 
 int /*<<< orphan*/ * remote_serial_open (char*) ; 
 int /*<<< orphan*/  remote_start_remote ; 
 int /*<<< orphan*/  serial_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_flush_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_raw (int /*<<< orphan*/ *) ; 
 scalar_t__ serial_setbaudrate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  symfile_objfile ; 
 int /*<<< orphan*/  target_preopen (int) ; 
 int /*<<< orphan*/  throw_exception (int) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  unpush_target (struct target_ops*) ; 
 int use_threadextra_query ; 
 int use_threadinfo_query ; 
 int wait_forever_enabled_p ; 

__attribute__((used)) static void
remote_open_1 (char *name, int from_tty, struct target_ops *target,
	       int extended_p, int async_p)
{
  int ex;
  struct remote_state *rs = get_remote_state ();
  if (name == 0)
    error ("To open a remote debug connection, you need to specify what\n"
	   "serial device is attached to the remote system\n"
	   "(e.g. /dev/ttyS0, /dev/ttya, COM1, etc.).");

  /* See FIXME above */
  if (!async_p)
    wait_forever_enabled_p = 1;

  target_preopen (from_tty);

  unpush_target (target);

  remote_desc = remote_serial_open (name);
  if (!remote_desc)
    perror_with_name (name);

  if (baud_rate != -1)
    {
      if (serial_setbaudrate (remote_desc, baud_rate))
	{
	  /* The requested speed could not be set.  Error out to
	     top level after closing remote_desc.  Take care to
	     set remote_desc to NULL to avoid closing remote_desc
	     more than once.  */
	  serial_close (remote_desc);
	  remote_desc = NULL;
	  perror_with_name (name);
	}
    }

  serial_raw (remote_desc);

  /* If there is something sitting in the buffer we might take it as a
     response to a command, which would be bad.  */
  serial_flush_input (remote_desc);

  if (from_tty)
    {
      puts_filtered ("Remote debugging using ");
      puts_filtered (name);
      puts_filtered ("\n");
    }
  push_target (target);		/* Switch to using remote target now */

  init_all_packet_configs ();

  general_thread = -2;
  continue_thread = -2;

  /* Probe for ability to use "ThreadInfo" query, as required.  */
  use_threadinfo_query = 1;
  use_threadextra_query = 1;

  /* Without this, some commands which require an active target (such
     as kill) won't work.  This variable serves (at least) double duty
     as both the pid of the target process (if it has such), and as a
     flag indicating that a target is active.  These functions should
     be split out into seperate variables, especially since GDB will
     someday have a notion of debugging several processes.  */

  inferior_ptid = pid_to_ptid (MAGIC_NULL_PID);

  if (async_p)
    {
      /* With this target we start out by owning the terminal. */
      remote_async_terminal_ours_p = 1;

      /* FIXME: cagney/1999-09-23: During the initial connection it is
	 assumed that the target is already ready and able to respond to
	 requests. Unfortunately remote_start_remote() eventually calls
	 wait_for_inferior() with no timeout.  wait_forever_enabled_p gets
	 around this. Eventually a mechanism that allows
	 wait_for_inferior() to expect/get timeouts will be
	 implemented. */
      wait_forever_enabled_p = 0;
    }

#ifdef SOLIB_CREATE_INFERIOR_HOOK
  /* First delete any symbols previously loaded from shared libraries. */
  no_shared_libraries (NULL, 0);
#endif

  /* Start the remote connection.  If error() or QUIT, discard this
     target (we'd otherwise be in an inconsistent state) and then
     propogate the error on up the exception chain.  This ensures that
     the caller doesn't stumble along blindly assuming that the
     function succeeded.  The CLI doesn't have this problem but other
     UI's, such as MI do.

     FIXME: cagney/2002-05-19: Instead of re-throwing the exception,
     this function should return an error indication letting the
     caller restore the previous state.  Unfortunately the command
     ``target remote'' is directly wired to this function making that
     impossible.  On a positive note, the CLI side of this problem has
     been fixed - the function set_cmd_context() makes it possible for
     all the ``target ....'' commands to share a common callback
     function.  See cli-dump.c.  */
  ex = catch_exceptions (uiout,
			 remote_start_remote, NULL,
			 "Couldn't establish connection to remote"
			 " target\n",
			 RETURN_MASK_ALL);
  if (ex < 0)
    {
      pop_target ();
      if (async_p)
	wait_forever_enabled_p = 1;
      throw_exception (ex);
    }

  if (async_p)
    wait_forever_enabled_p = 1;

  if (extended_p)
    {
      /* Tell the remote that we are using the extended protocol.  */
      char *buf = alloca (rs->remote_packet_size);
      putpkt ("!");
      getpkt (buf, (rs->remote_packet_size), 0);
    }
#ifdef SOLIB_CREATE_INFERIOR_HOOK
  /* FIXME: need a master target_open vector from which all
     remote_opens can be called, so that stuff like this can
     go there.  Failing that, the following code must be copied
     to the open function for any remote target that wants to
     support svr4 shared libraries.  */

  /* Set up to detect and load shared libraries. */
  if (exec_bfd) 	/* No use without an exec file. */
    {
      SOLIB_CREATE_INFERIOR_HOOK (PIDGET (inferior_ptid));
      remote_check_symbols (symfile_objfile);
    }
#endif
}