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
struct opie {int opie_n; } ;

/* Variables and functions */
 int opiegetsequence (struct opie*) ; 

int testgetsequence()
{
  struct opie testin;
  testin.opie_n = 42;

  if (opiegetsequence(&testin) != 42)
    return -1;

  return 0;
}