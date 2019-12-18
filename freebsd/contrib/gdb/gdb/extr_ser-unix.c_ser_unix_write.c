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
struct serial {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int write (int /*<<< orphan*/ ,char const*,int) ; 

int
ser_unix_write (struct serial *scb, const char *str, int len)
{
  int cc;

  while (len > 0)
    {
      cc = write (scb->fd, str, len);

      if (cc < 0)
	return 1;
      len -= cc;
      str += cc;
    }
  return 0;
}