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
struct TYPE_2__ {unsigned char (* wait ) (char*) ;} ;

/* Variables and functions */
 int server_waiting ; 
 unsigned char stub1 (char*) ; 
 TYPE_1__* the_target ; 

unsigned char
mywait (char *statusp, int connected_wait)
{
  unsigned char ret;

  if (connected_wait)
    server_waiting = 1;

  ret = (*the_target->wait) (statusp);

  if (connected_wait)
    server_waiting = 0;

  return ret;
}