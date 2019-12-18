#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
typedef  int /*<<< orphan*/  ULONGEST ;
struct TYPE_4__ {scalar_t__ support; } ;

/* Variables and functions */
 scalar_t__ PACKET_DISABLE ; 
 scalar_t__ PACKET_OK ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int TARGET_SIGNAL_0 ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexnumstr (char*,int /*<<< orphan*/ ) ; 
 int last_sent_signal ; 
 int last_sent_step ; 
 scalar_t__ packet_ok (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 TYPE_1__ remote_protocol_E ; 
 TYPE_1__ remote_protocol_e ; 
 scalar_t__ remote_vcont_resume (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_thread (int,int /*<<< orphan*/ ) ; 
 scalar_t__ step_range_end ; 
 scalar_t__ step_range_start ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  target_resume_hook () ; 
 void* tohex (int) ; 

__attribute__((used)) static void
remote_resume (ptid_t ptid, int step, enum target_signal siggnal)
{
  struct remote_state *rs = get_remote_state ();
  char *buf = alloca (rs->remote_packet_size);
  int pid = PIDGET (ptid);
  char *p;

  last_sent_signal = siggnal;
  last_sent_step = step;

  /* A hook for when we need to do something at the last moment before
     resumption.  */
  if (target_resume_hook)
    (*target_resume_hook) ();

  /* The vCont packet doesn't need to specify threads via Hc.  */
  if (remote_vcont_resume (ptid, step, siggnal))
    return;

  /* All other supported resume packets do use Hc, so call set_thread.  */
  if (pid == -1)
    set_thread (0, 0);		/* run any thread */
  else
    set_thread (pid, 0);	/* run this thread */

  /* The s/S/c/C packets do not return status.  So if the target does
     not support the S or C packets, the debug agent returns an empty
     string which is detected in remote_wait().  This protocol defect
     is fixed in the e/E packets. */

  if (step && step_range_end)
    {
      /* If the target does not support the 'E' packet, we try the 'S'
	 packet.  Ideally we would fall back to the 'e' packet if that
	 too is not supported.  But that would require another copy of
	 the code to issue the 'e' packet (and fall back to 's' if not
	 supported) in remote_wait().  */

      if (siggnal != TARGET_SIGNAL_0)
	{
	  if (remote_protocol_E.support != PACKET_DISABLE)
	    {
	      p = buf;
	      *p++ = 'E';
	      *p++ = tohex (((int) siggnal >> 4) & 0xf);
	      *p++ = tohex (((int) siggnal) & 0xf);
	      *p++ = ',';
	      p += hexnumstr (p, (ULONGEST) step_range_start);
	      *p++ = ',';
	      p += hexnumstr (p, (ULONGEST) step_range_end);
	      *p++ = 0;

	      putpkt (buf);
	      getpkt (buf, (rs->remote_packet_size), 0);

	      if (packet_ok (buf, &remote_protocol_E) == PACKET_OK)
		return;
	    }
	}
      else
	{
	  if (remote_protocol_e.support != PACKET_DISABLE)
	    {
	      p = buf;
	      *p++ = 'e';
	      p += hexnumstr (p, (ULONGEST) step_range_start);
	      *p++ = ',';
	      p += hexnumstr (p, (ULONGEST) step_range_end);
	      *p++ = 0;

	      putpkt (buf);
	      getpkt (buf, (rs->remote_packet_size), 0);

	      if (packet_ok (buf, &remote_protocol_e) == PACKET_OK)
		return;
	    }
	}
    }

  if (siggnal != TARGET_SIGNAL_0)
    {
      buf[0] = step ? 'S' : 'C';
      buf[1] = tohex (((int) siggnal >> 4) & 0xf);
      buf[2] = tohex (((int) siggnal) & 0xf);
      buf[3] = '\0';
    }
  else
    strcpy (buf, step ? "s" : "c");

  putpkt (buf);
}