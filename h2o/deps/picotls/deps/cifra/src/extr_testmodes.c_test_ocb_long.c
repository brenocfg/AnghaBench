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
 int /*<<< orphan*/  check_ocb_long (int,char*,int) ; 

__attribute__((used)) static void test_ocb_long(void)
{
  check_ocb_long(16, "\x67\xE9\x44\xD2\x32\x56\xC5\xE0\xB6\xC6\x1F\xA2\x2F\xDF\x1E\xA2", 16);
  check_ocb_long(24, "\xF6\x73\xF2\xC3\xE7\x17\x4A\xAE\x7B\xAE\x98\x6C\xA9\xF2\x9E\x17", 16);
  check_ocb_long(32, "\xD9\x0E\xB8\xE9\xC9\x77\xC8\x8B\x79\xDD\x79\x3D\x7F\xFA\x16\x1C", 16);
  check_ocb_long(16, "\x77\xA3\xD8\xE7\x35\x89\x15\x8D\x25\xD0\x12\x09", 12);
  check_ocb_long(24, "\x05\xD5\x6E\xAD\x27\x52\xC8\x6B\xE6\x93\x2C\x5E", 12);
  check_ocb_long(32, "\x54\x58\x35\x9A\xC2\x3B\x0C\xBA\x9E\x63\x30\xDD", 12);
  check_ocb_long(16, "\x19\x2C\x9B\x7B\xD9\x0B\xA0\x6A", 8);
  check_ocb_long(24, "\x00\x66\xBC\x6E\x0E\xF3\x4E\x24", 8);
  check_ocb_long(32, "\x7D\x4E\xA5\xD4\x45\x50\x1C\xBE", 8);
}