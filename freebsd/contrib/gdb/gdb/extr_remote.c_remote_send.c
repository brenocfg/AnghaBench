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
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  getpkt (char*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putpkt (char*) ; 

__attribute__((used)) static void
remote_send (char *buf,
	     long sizeof_buf)
{
  putpkt (buf);
  getpkt (buf, sizeof_buf, 0);

  if (buf[0] == 'E')
    error ("Remote failure reply: %s", buf);
}