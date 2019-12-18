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
 char* files_start ; 
 void* heap ; 
 void* memory_limit ; 
 char* next_free ; 

_initialize_standalone (void)
{
  char *next;

  /* Find start of data on files.  */

  files_start = heap;

  /* Find the end of the data on files.  */

  for (next = files_start; *(int *) next; next += *(int *) next)
    {
    }

  /* That is where free storage starts for sbrk to give out.  */
  next_free = next;

  memory_limit = heap + sizeof heap;
}