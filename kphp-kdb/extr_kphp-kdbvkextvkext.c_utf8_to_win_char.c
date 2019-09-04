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
 int* utf8_to_win_convert_0x000 ; 
 int* utf8_to_win_convert_0x2000 ; 
 int* utf8_to_win_convert_0x2100 ; 
 int* utf8_to_win_convert_0x400 ; 
 int* utf8_to_win_convert_0xff00 ; 

int utf8_to_win_char (int c) {
  if (c < 0x80) {
    return c;
  }
  if (c == 8238 || c == 8236 || c == 8235) return 0xda; 
  switch (c & ~0xff) {
    case 0x400: return utf8_to_win_convert_0x400[c & 0xff];
    case 0x2000: return utf8_to_win_convert_0x2000[c & 0xff];
    case 0xff00: return utf8_to_win_convert_0xff00[c & 0xff];
    case 0x2100: return utf8_to_win_convert_0x2100[c & 0xff];
    case 0x000: return utf8_to_win_convert_0x000[c & 0xff];
  }
  return -1;
}