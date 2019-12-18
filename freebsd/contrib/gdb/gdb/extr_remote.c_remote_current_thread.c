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
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 char* alloca (int /*<<< orphan*/ ) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_to_ptid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ptid_t
remote_current_thread (ptid_t oldpid)
{
  struct remote_state *rs = get_remote_state ();
  char *buf = alloca (rs->remote_packet_size);

  putpkt ("qC");
  getpkt (buf, (rs->remote_packet_size), 0);
  if (buf[0] == 'Q' && buf[1] == 'C')
    return pid_to_ptid (strtol (&buf[2], NULL, 16));
  else
    return oldpid;
}