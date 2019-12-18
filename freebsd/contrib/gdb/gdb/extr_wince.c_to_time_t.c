#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dwLowDateTime; scalar_t__ dwHighDateTime; } ;
typedef  TYPE_1__ FILETIME ;

/* Variables and functions */
 scalar_t__ FACTOR ; 
 int NSPERSEC ; 

long
to_time_t (FILETIME * ptr)
{
  /* A file time is the number of 100ns since jan 1 1601
     stuffed into two long words.
     A time_t is the number of seconds since jan 1 1970.  */

  long rem;
  long long x = ((long long) ptr->dwHighDateTime << 32) + ((unsigned) ptr->dwLowDateTime);
  x -= FACTOR;			/* number of 100ns between 1601 and 1970 */
  rem = x % ((long long) NSPERSEC);
  rem += (NSPERSEC / 2);
  x /= (long long) NSPERSEC;	/* number of 100ns in a second */
  x += (long long) (rem / NSPERSEC);
  return x;
}