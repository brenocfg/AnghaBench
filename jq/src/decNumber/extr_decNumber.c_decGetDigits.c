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
typedef  int /*<<< orphan*/  uInt ;
typedef  int Unit ;
typedef  int /*<<< orphan*/  LI ;
typedef  int Int ;

/* Variables and functions */
 int DECDPUN ; 
 int* powers ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Int decGetDigits(Unit *uar, Int len) {
  Unit *up=uar+(len-1);            // -> msu
  Int  digits=(len-1)*DECDPUN+1;   // possible digits excluding msu
  #if DECDPUN>4
  uInt const *pow;                 // work
  #endif
                                   // (at least 1 in final msu)
  #if DECCHECK
  if (len<1) printf("decGetDigits called with len<1 [%ld]\n", (LI)len);
  #endif

  for (; up>=uar; up--) {
    if (*up==0) {                  // unit is all 0s
      if (digits==1) break;        // a zero has one digit
      digits-=DECDPUN;             // adjust for 0 unit
      continue;}
    // found the first (most significant) non-zero Unit
    #if DECDPUN>1                  // not done yet
    if (*up<10) break;             // is 1-9
    digits++;
    #if DECDPUN>2                  // not done yet
    if (*up<100) break;            // is 10-99
    digits++;
    #if DECDPUN>3                  // not done yet
    if (*up<1000) break;           // is 100-999
    digits++;
    #if DECDPUN>4                  // count the rest ...
    for (pow=&powers[4]; *up>=*pow; pow++) digits++;
    #endif
    #endif
    #endif
    #endif
    break;
    } // up
  return digits;
  }