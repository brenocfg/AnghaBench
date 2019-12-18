#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fd; } ;
typedef  TYPE_1__ WSPipeOut ;

/* Variables and functions */
 TYPE_1__* xcalloc (int,int) ; 

__attribute__((used)) static WSPipeOut *
new_wspipeout (void)
{
  WSPipeOut *pipeout = xcalloc (1, sizeof (WSPipeOut));
  pipeout->fd = -1;

  return pipeout;
}