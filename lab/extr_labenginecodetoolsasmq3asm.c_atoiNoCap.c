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
typedef  scalar_t__ INT64 ;

/* Variables and functions */
 scalar_t__ atoi64 (char const*) ; 

__attribute__((used)) static int atoiNoCap (const char *s)
{
  INT64 l;
  union {
    unsigned int u;
    signed int i;
  } retval;

  l = atoi64(s);
  /* Now smash to signed 32 bits accordingly. */
  if (l < 0) {
    retval.i = (int)l;
  } else {
    retval.u = (unsigned int)l;
  }
  return retval.i;  /* <- union hackage.  I feel dirty with this.  -PH */
}