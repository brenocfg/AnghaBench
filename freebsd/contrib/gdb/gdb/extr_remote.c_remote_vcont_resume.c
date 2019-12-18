#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct remote_state {scalar_t__ remote_packet_size; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
struct TYPE_2__ {scalar_t__ support; } ;

/* Variables and functions */
 int MAGIC_NULL_PID ; 
 scalar_t__ PACKET_DISABLE ; 
 scalar_t__ PACKET_SUPPORT_UNKNOWN ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int TARGET_SIGNAL_0 ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 TYPE_1__ remote_protocol_vcont ; 
 int /*<<< orphan*/  remote_vcont_probe (struct remote_state*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  xfree ; 
 char* xmalloc (scalar_t__) ; 
 char* xstrprintf (char*,...) ; 

__attribute__((used)) static int
remote_vcont_resume (ptid_t ptid, int step, enum target_signal siggnal)
{
  struct remote_state *rs = get_remote_state ();
  int pid = PIDGET (ptid);
  char *buf = NULL, *outbuf;
  struct cleanup *old_cleanup;

  buf = xmalloc (rs->remote_packet_size);
  old_cleanup = make_cleanup (xfree, buf);

  if (remote_protocol_vcont.support == PACKET_SUPPORT_UNKNOWN)
    remote_vcont_probe (rs, buf);

  if (remote_protocol_vcont.support == PACKET_DISABLE)
    {
      do_cleanups (old_cleanup);
      return 0;
    }

  /* If we could generate a wider range of packets, we'd have to worry
     about overflowing BUF.  Should there be a generic
     "multi-part-packet" packet?  */

  if (PIDGET (inferior_ptid) == MAGIC_NULL_PID)
    {
      /* MAGIC_NULL_PTID means that we don't have any active threads, so we
	 don't have any PID numbers the inferior will understand.  Make sure
	 to only send forms that do not specify a PID.  */
      if (step && siggnal != TARGET_SIGNAL_0)
	outbuf = xstrprintf ("vCont;S%02x", siggnal);
      else if (step)
	outbuf = xstrprintf ("vCont;s");
      else if (siggnal != TARGET_SIGNAL_0)
	outbuf = xstrprintf ("vCont;C%02x", siggnal);
      else
	outbuf = xstrprintf ("vCont;c");
    }
  else if (pid == -1)
    {
      /* Resume all threads, with preference for INFERIOR_PTID.  */
      if (step && siggnal != TARGET_SIGNAL_0)
	outbuf = xstrprintf ("vCont;S%02x:%x;c", siggnal,
			     PIDGET (inferior_ptid));
      else if (step)
	outbuf = xstrprintf ("vCont;s:%x;c", PIDGET (inferior_ptid));
      else if (siggnal != TARGET_SIGNAL_0)
	outbuf = xstrprintf ("vCont;C%02x:%x;c", siggnal,
			     PIDGET (inferior_ptid));
      else
	outbuf = xstrprintf ("vCont;c");
    }
  else
    {
      /* Scheduler locking; resume only PTID.  */
      if (step && siggnal != TARGET_SIGNAL_0)
	outbuf = xstrprintf ("vCont;S%02x:%x", siggnal, pid);
      else if (step)
	outbuf = xstrprintf ("vCont;s:%x", pid);
      else if (siggnal != TARGET_SIGNAL_0)
	outbuf = xstrprintf ("vCont;C%02x:%x", siggnal, pid);
      else
	outbuf = xstrprintf ("vCont;c:%x", pid);
    }

  gdb_assert (outbuf && strlen (outbuf) < rs->remote_packet_size);
  make_cleanup (xfree, outbuf);

  putpkt (outbuf);

  do_cleanups (old_cleanup);

  return 1;
}