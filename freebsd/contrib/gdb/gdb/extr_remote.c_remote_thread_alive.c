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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpkt (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int
remote_thread_alive (ptid_t ptid)
{
  int tid = PIDGET (ptid);
  char buf[16];

  if (tid < 0)
    sprintf (buf, "T-%08x", -tid);
  else
    sprintf (buf, "T%08x", tid);
  putpkt (buf);
  getpkt (buf, sizeof (buf), 0);
  return (buf[0] == 'O' && buf[1] == 'K');
}