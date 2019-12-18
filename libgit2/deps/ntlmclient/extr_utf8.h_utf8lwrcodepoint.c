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
typedef  int utf8_int32_t ;

/* Variables and functions */

utf8_int32_t utf8lwrcodepoint(utf8_int32_t cp) {
  if (((0x0041 <= cp) && (0x005a >= cp)) ||
      ((0x00c0 <= cp) && (0x00d6 >= cp)) ||
      ((0x00d8 <= cp) && (0x00de >= cp)) ||
      ((0x0391 <= cp) && (0x03a1 >= cp)) ||
      ((0x03a3 <= cp) && (0x03ab >= cp))) {
    cp += 32;
  } else if (((0x0100 <= cp) && (0x012f >= cp)) ||
             ((0x0132 <= cp) && (0x0137 >= cp)) ||
             ((0x014a <= cp) && (0x0177 >= cp)) ||
             ((0x0182 <= cp) && (0x0185 >= cp)) ||
             ((0x01a0 <= cp) && (0x01a5 >= cp)) ||
             ((0x01de <= cp) && (0x01ef >= cp)) ||
             ((0x01f8 <= cp) && (0x021f >= cp)) ||
             ((0x0222 <= cp) && (0x0233 >= cp)) ||
             ((0x0246 <= cp) && (0x024f >= cp)) ||
             ((0x03d8 <= cp) && (0x03ef >= cp))) {
    cp |= 0x1;
  } else if (((0x0139 <= cp) && (0x0148 >= cp)) ||
             ((0x0179 <= cp) && (0x017e >= cp)) ||
             ((0x01af <= cp) && (0x01b0 >= cp)) ||
             ((0x01b3 <= cp) && (0x01b6 >= cp)) ||
             ((0x01cd <= cp) && (0x01dc >= cp))) {
    cp += 1;
    cp &= ~0x1;
  } else {
    switch (cp) {
    default: break;
    case 0x0178: cp = 0x00ff; break;
    case 0x0243: cp = 0x0180; break;
    case 0x018e: cp = 0x01dd; break;
    case 0x023d: cp = 0x019a; break;
    case 0x0220: cp = 0x019e; break;
    case 0x01b7: cp = 0x0292; break;
    case 0x01c4: cp = 0x01c6; break;
    case 0x01c7: cp = 0x01c9; break;
    case 0x01ca: cp = 0x01cc; break;
    case 0x01f1: cp = 0x01f3; break;
    case 0x01f7: cp = 0x01bf; break;
    case 0x0187: cp = 0x0188; break;
    case 0x018b: cp = 0x018c; break;
    case 0x0191: cp = 0x0192; break;
    case 0x0198: cp = 0x0199; break;
    case 0x01a7: cp = 0x01a8; break;
    case 0x01ac: cp = 0x01ad; break;
    case 0x01af: cp = 0x01b0; break;
    case 0x01b8: cp = 0x01b9; break;
    case 0x01bc: cp = 0x01bd; break;
    case 0x01f4: cp = 0x01f5; break;
    case 0x023b: cp = 0x023c; break;
    case 0x0241: cp = 0x0242; break;
    case 0x03fd: cp = 0x037b; break;
    case 0x03fe: cp = 0x037c; break;
    case 0x03ff: cp = 0x037d; break;
    case 0x037f: cp = 0x03f3; break;
    case 0x0386: cp = 0x03ac; break;
    case 0x0388: cp = 0x03ad; break;
    case 0x0389: cp = 0x03ae; break;
    case 0x038a: cp = 0x03af; break;
    case 0x038c: cp = 0x03cc; break;
    case 0x038e: cp = 0x03cd; break;
    case 0x038f: cp = 0x03ce; break;
    case 0x0370: cp = 0x0371; break;
    case 0x0372: cp = 0x0373; break;
    case 0x0376: cp = 0x0377; break;
    case 0x03f4: cp = 0x03d1; break;
    case 0x03cf: cp = 0x03d7; break;
    case 0x03f9: cp = 0x03f2; break;
    case 0x03f7: cp = 0x03f8; break;
    case 0x03fa: cp = 0x03fb; break;
    };
  }

  return cp;
}