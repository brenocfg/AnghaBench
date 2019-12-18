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
struct serial {scalar_t__ bufcnt; int /*<<< orphan*/  buf; int /*<<< orphan*/  bufp; } ;

/* Variables and functions */
 int SERIAL_ERROR ; 

int
ser_unix_flush_input (struct serial *scb)
{
  if (scb->bufcnt >= 0)
    {
      scb->bufcnt = 0;
      scb->bufp = scb->buf;
      return 0;
    }
  else
    return SERIAL_ERROR;
}