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
 int /*<<< orphan*/  write_buff_char (int) ; 
 int /*<<< orphan*/  write_buff_char_2 (int,int) ; 
 int /*<<< orphan*/  write_buff_char_3 (int,int,int) ; 
 int /*<<< orphan*/  write_buff_char_4 (int,int,int,int) ; 

void write_utf8_char (int c) {
  if (c < 128) {
    write_buff_char (c);
    return;
  }
  if (c < 0x800) {
    write_buff_char_2 (0xc0 + (c >> 6), 0x80 + (c & 63));
    return;
  }  
  if (c < 0x10000) {
    write_buff_char_3 (0xe0 + (c >> 12), 0x80 + ((c >> 6) & 63), 0x80 + (c & 63));
    return;
  }
  if (c < 0x200000) {
    write_buff_char_4 (0xf0 + (c >> 18), 0x80 + ((c >> 12) & 63), 0x80 + ((c >> 6) & 63), 0x80 + (c & 63));
    return;
  }
}