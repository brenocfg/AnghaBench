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
typedef  int UInt64 ;
typedef  int UInt32 ;
struct TYPE_3__ {int Low; scalar_t__ High; } ;
typedef  TYPE_1__ CNtfsFileTime ;
typedef  int Byte ;

/* Variables and functions */
 int PERIOD_100 ; 
 int PERIOD_4 ; 
 int PERIOD_400 ; 
 char* UIntToStr (char*,unsigned int,int) ; 
 int /*<<< orphan*/  UIntToStr_2 (char*,unsigned int) ; 

__attribute__((used)) static void ConvertFileTimeToString(const CNtfsFileTime *nt, char *s)
{
  unsigned year, mon, hour, min, sec;
  Byte ms[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  unsigned t;
  UInt32 v;
  UInt64 v64 = nt->Low | ((UInt64)nt->High << 32);
  v64 /= 10000000;
  sec = (unsigned)(v64 % 60); v64 /= 60;
  min = (unsigned)(v64 % 60); v64 /= 60;
  hour = (unsigned)(v64 % 24); v64 /= 24;

  v = (UInt32)v64;

  year = (unsigned)(1601 + v / PERIOD_400 * 400);
  v %= PERIOD_400;

  t = v / PERIOD_100; if (t ==  4) t =  3; year += t * 100; v -= t * PERIOD_100;
  t = v / PERIOD_4;   if (t == 25) t = 24; year += t * 4;   v -= t * PERIOD_4;
  t = v / 365;        if (t ==  4) t =  3; year += t;       v -= t * 365;

  if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    ms[1] = 29;
  for (mon = 0;; mon++)
  {
    unsigned d = ms[mon];
    if (v < d)
      break;
    v -= d;
  }
  s = UIntToStr(s, year, 4); *s++ = '-';
  UIntToStr_2(s, mon + 1); s[2] = '-'; s += 3;
  UIntToStr_2(s, (unsigned)v + 1); s[2] = ' '; s += 3;
  UIntToStr_2(s, hour); s[2] = ':'; s += 3;
  UIntToStr_2(s, min); s[2] = ':'; s += 3;
  UIntToStr_2(s, sec); s[2] = 0;
}