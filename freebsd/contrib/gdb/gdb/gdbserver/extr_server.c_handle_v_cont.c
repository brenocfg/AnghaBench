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
struct thread_resume {int thread; int leave_stopped; int step; scalar_t__ sig; } ;
typedef  int /*<<< orphan*/  resume_info ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct thread_resume*) ;} ;

/* Variables and functions */
 int cont_thread ; 
 int /*<<< orphan*/  free (struct thread_resume*) ; 
 struct thread_resume* malloc (int) ; 
 unsigned char mywait (char*,int) ; 
 int /*<<< orphan*/  prepare_resume_reply (char*,char,unsigned char) ; 
 int /*<<< orphan*/  set_desired_inferior (int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 void* strtol (char*,char**,int) ; 
 int /*<<< orphan*/  stub1 (struct thread_resume*) ; 
 scalar_t__ target_signal_to_host (int) ; 
 int /*<<< orphan*/  target_signal_to_host_p (int) ; 
 TYPE_1__* the_target ; 

void
handle_v_cont (char *own_buf, char *status, unsigned char *signal)
{
  char *p, *q;
  int n = 0, i = 0;
  struct thread_resume *resume_info, default_action;

  /* Count the number of semicolons in the packet.  There should be one
     for every action.  */
  p = &own_buf[5];
  while (p)
    {
      n++;
      p++;
      p = strchr (p, ';');
    }
  /* Allocate room for one extra action, for the default remain-stopped
     behavior; if no default action is in the list, we'll need the extra
     slot.  */
  resume_info = malloc ((n + 1) * sizeof (resume_info[0]));

  default_action.thread = -1;
  default_action.leave_stopped = 1;
  default_action.step = 0;
  default_action.sig = 0;

  p = &own_buf[5];
  i = 0;
  while (*p)
    {
      p++;

      resume_info[i].leave_stopped = 0;

      if (p[0] == 's' || p[0] == 'S')
	resume_info[i].step = 1;
      else if (p[0] == 'c' || p[0] == 'C')
	resume_info[i].step = 0;
      else
	goto err;

      if (p[0] == 'S' || p[0] == 'C')
	{
	  int sig;
	  sig = strtol (p + 1, &q, 16);
	  if (p == q)
	    goto err;
	  p = q;

	  if (!target_signal_to_host_p (sig))
	    goto err;
	  resume_info[i].sig = target_signal_to_host (sig);
	}
      else
	{
	  resume_info[i].sig = 0;
	  p = p + 1;
	}

      if (p[0] == 0)
	{
	  resume_info[i].thread = -1;
	  default_action = resume_info[i];

	  /* Note: we don't increment i here, we'll overwrite this entry
	     the next time through.  */
	}
      else if (p[0] == ':')
	{
	  resume_info[i].thread = strtol (p + 1, &q, 16);
	  if (p == q)
	    goto err;
	  p = q;
	  if (p[0] != ';' && p[0] != 0)
	    goto err;

	  i++;
	}
    }

  resume_info[i] = default_action;

  /* Still used in occasional places in the backend.  */
  if (n == 1 && resume_info[0].thread != -1)
    cont_thread = resume_info[0].thread;
  else
    cont_thread = -1;
  set_desired_inferior (0);

  (*the_target->resume) (resume_info);

  free (resume_info);

  *signal = mywait (status, 1);
  prepare_resume_reply (own_buf, *status, *signal);
  return;

err:
  /* No other way to report an error... */
  strcpy (own_buf, "");
  free (resume_info);
  return;
}