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
struct TYPE_2__ {int (* send_break ) (struct serial*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SERIAL_BREAK ; 
 int /*<<< orphan*/  serial_logchar (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * serial_logfp ; 
 int stub1 (struct serial*) ; 

int
serial_send_break (struct serial *scb)
{
  if (serial_logfp != NULL)
    serial_logchar (serial_logfp, 'w', SERIAL_BREAK, 0);

  return (scb->ops->send_break (scb));
}