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
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 scalar_t__ STACKSIZE ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ sp ; 
 int /*<<< orphan*/ * stack ; 

void push(WORD l)
{
  if(sp < STACKSIZE)
    stack[sp++] = l;
  else
    puts("Stack full");
}