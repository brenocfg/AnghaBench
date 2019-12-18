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

/* Variables and functions */
 int /*<<< orphan*/  handle_v_cont (char*,char*,unsigned char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void
handle_v_requests (char *own_buf, char *status, unsigned char *signal)
{
  if (strncmp (own_buf, "vCont;", 6) == 0)
    {
      handle_v_cont (own_buf, status, signal);
      return;
    }

  if (strncmp (own_buf, "vCont?", 6) == 0)
    {
      strcpy (own_buf, "vCont;c;C;s;S");
      return;
    }

  /* Otherwise we didn't know what packet it was.  Say we didn't
     understand it.  */
  own_buf[0] = 0;
  return;
}