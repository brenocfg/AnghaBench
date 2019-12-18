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
struct timeval {long tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  strtol (char const*,char**,int) ; 

__attribute__((used)) static char * strtotimeval(const char *str, struct timeval *tv)
{
  char *s;
  long fs;			/* Fractional seconds */
  int i;

  tv->tv_sec = strtol(str, &s, 10);
  fs = 0;

  if ( *s == '.' ) {
    s++;

    for ( i = 0 ; i < 6 ; i++ ) {
      if ( !isdigit(*s) )
	break;

      fs *= 10;
      fs += *s++ - '0';
    }

    for ( ; i < 6; i++ )
      fs *= 10;

    while ( isdigit(*s) )
      s++;
  }

  tv->tv_usec = fs;
  return s;
}