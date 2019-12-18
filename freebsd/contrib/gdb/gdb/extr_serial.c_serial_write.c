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
struct serial {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* write ) (struct serial*,char const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_logchar (int /*<<< orphan*/ *,char,char const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * serial_logfp ; 
 int stub1 (struct serial*,char const*,int) ; 

int
serial_write (struct serial *scb, const char *str, int len)
{
  if (serial_logfp != NULL)
    {
      int count;

      for (count = 0; count < len; count++)
	serial_logchar (serial_logfp, 'w', str[count] & 0xff, 0);

      /* Make sure that the log file is as up-to-date as possible,
         in case we are getting ready to dump core or something. */
      gdb_flush (serial_logfp);
    }

  return (scb->ops->write (scb, str, len));
}