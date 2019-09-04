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
 int /*<<< orphan*/  assert (int) ; 
 int jvp_utf8_encode_length (int) ; 

int jvp_utf8_encode(int codepoint, char* out) {
  assert(codepoint >= 0 && codepoint <= 0x10FFFF);
  char* start = out;
  if (codepoint <= 0x7F) {
    *out++ = codepoint;
  } else if (codepoint <= 0x7FF) {
    *out++ = 0xC0 + ((codepoint & 0x7C0) >> 6);
    *out++ = 0x80 + ((codepoint & 0x03F));
  } else if(codepoint <= 0xFFFF) {
    *out++ = 0xE0 + ((codepoint & 0xF000) >> 12);
    *out++ = 0x80 + ((codepoint & 0x0FC0) >> 6);
    *out++ = 0x80 + ((codepoint & 0x003F));
  } else {
    *out++ = 0xF0 + ((codepoint & 0x1C0000) >> 18);
    *out++ = 0x80 + ((codepoint & 0x03F000) >> 12);
    *out++ = 0x80 + ((codepoint & 0x000FC0) >> 6);
    *out++ = 0x80 + ((codepoint & 0x00003F));
  }
  assert(out - start == jvp_utf8_encode_length(codepoint));
  return out - start;
}