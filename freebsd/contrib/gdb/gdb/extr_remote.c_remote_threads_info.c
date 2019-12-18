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
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 scalar_t__ remote_desc ; 
 int /*<<< orphan*/  remote_find_new_threads () ; 
 int strtol (char*,char**,int) ; 
 scalar_t__ use_threadinfo_query ; 

__attribute__((used)) static void
remote_threads_info (void)
{
  struct remote_state *rs = get_remote_state ();
  char *buf = alloca (rs->remote_packet_size);
  char *bufp;
  int tid;

  if (remote_desc == 0)		/* paranoia */
    error ("Command can only be used when connected to the remote target.");

  if (use_threadinfo_query)
    {
      putpkt ("qfThreadInfo");
      bufp = buf;
      getpkt (bufp, (rs->remote_packet_size), 0);
      if (bufp[0] != '\0')		/* q packet recognized */
	{
	  while (*bufp++ == 'm')	/* reply contains one or more TID */
	    {
	      do
		{
		  tid = strtol (bufp, &bufp, 16);
		  if (tid != 0 && !in_thread_list (pid_to_ptid (tid)))
		    add_thread (pid_to_ptid (tid));
		}
	      while (*bufp++ == ',');	/* comma-separated list */
	      putpkt ("qsThreadInfo");
	      bufp = buf;
	      getpkt (bufp, (rs->remote_packet_size), 0);
	    }
	  return;	/* done */
	}
    }

  /* Else fall back to old method based on jmetzler protocol. */
  use_threadinfo_query = 0;
  remote_find_new_threads ();
  return;
}