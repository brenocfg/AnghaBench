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
struct TYPE_2__ {int (* write_memory ) (int /*<<< orphan*/ ,char*,int) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  check_mem_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* the_target ; 

int
write_inferior_memory (CORE_ADDR memaddr, const char *myaddr, int len)
{
  /* Lacking cleanups, there is some potential for a memory leak if the
     write fails and we go through error().  Make sure that no more than
     one buffer is ever pending by making BUFFER static.  */
  static char *buffer = 0;
  int res;

  if (buffer != NULL)
    free (buffer);

  buffer = malloc (len);
  memcpy (buffer, myaddr, len);
  check_mem_write (memaddr, buffer, len);
  res = (*the_target->write_memory) (memaddr, buffer, len);
  free (buffer);
  buffer = NULL;

  return res;
}