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
typedef  scalar_t__ utf8proc_uint8_t ;
typedef  int utf8proc_ssize_t ;
typedef  int utf8proc_int32_t ;

/* Variables and functions */

__attribute__((used)) static utf8proc_ssize_t unsafe_encode_char(utf8proc_int32_t uc, utf8proc_uint8_t *dst) {
   if (uc < 0x00) {
      return 0;
   } else if (uc < 0x80) {
      dst[0] = (utf8proc_uint8_t)uc;
      return 1;
   } else if (uc < 0x800) {
      dst[0] = (utf8proc_uint8_t)(0xC0 + (uc >> 6));
      dst[1] = (utf8proc_uint8_t)(0x80 + (uc & 0x3F));
      return 2;
   } else if (uc == 0xFFFF) {
       dst[0] = (utf8proc_uint8_t)0xFF;
       return 1;
   } else if (uc == 0xFFFE) {
       dst[0] = (utf8proc_uint8_t)0xFE;
       return 1;
   } else if (uc < 0x10000) {
      dst[0] = (utf8proc_uint8_t)(0xE0 + (uc >> 12));
      dst[1] = (utf8proc_uint8_t)(0x80 + ((uc >> 6) & 0x3F));
      dst[2] = (utf8proc_uint8_t)(0x80 + (uc & 0x3F));
      return 3;
   } else if (uc < 0x110000) {
      dst[0] = (utf8proc_uint8_t)(0xF0 + (uc >> 18));
      dst[1] = (utf8proc_uint8_t)(0x80 + ((uc >> 12) & 0x3F));
      dst[2] = (utf8proc_uint8_t)(0x80 + ((uc >> 6) & 0x3F));
      dst[3] = (utf8proc_uint8_t)(0x80 + (uc & 0x3F));
      return 4;
   } else return 0;
}