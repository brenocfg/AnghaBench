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
 int MAGIC_NULL_PID ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 int continue_thread ; 
 int general_thread ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void
set_thread (int th, int gen)
{
  struct remote_state *rs = get_remote_state ();
  char *buf = alloca (rs->remote_packet_size);
  int state = gen ? general_thread : continue_thread;

  if (state == th)
    return;

  buf[0] = 'H';
  buf[1] = gen ? 'g' : 'c';
  if (th == MAGIC_NULL_PID)
    {
      buf[2] = '0';
      buf[3] = '\0';
    }
  else if (th < 0)
    sprintf (&buf[2], "-%x", -th);
  else
    sprintf (&buf[2], "%x", th);
  putpkt (buf);
  getpkt (buf, (rs->remote_packet_size), 0);
  if (gen)
    general_thread = th;
  else
    continue_thread = th;
}