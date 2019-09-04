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
 int cur_buff_len ; 
 int utf8_to_win_char (int) ; 
 int /*<<< orphan*/  write_buff (char*,int) ; 
 int /*<<< orphan*/  write_buff_char (char) ; 
 int /*<<< orphan*/  write_buff_long (int) ; 

int utf8_to_win (const char *s, int len, int max_len, int exit_on_error) {
  int st = 0;
  int acc = 0;
  int i;
  if (max_len && len > 3 * max_len) {
    len = 3 * max_len;
  }
  for (i = 0; i < len; i++) {
    if (max_len && cur_buff_len > max_len) {
      break;
    }
    unsigned char c = s[i];
    if (c < 0x80) {
      if (st) {
        if (exit_on_error) {
          return -1;
        }
        write_buff ("?1?", 3);
      }
      write_buff_char (c);
      st = 0;
      continue;
    }
    if ((c & 0xc0) == 0x80) {
      if (!st) {
        if (exit_on_error) {
          return -1;
        }
        write_buff ("?2?", 3);
        continue;
      }
      acc <<= 6;
      acc += c - 0x80;
      if (!--st) {
        if (exit_on_error && acc < 0x80) {
          return -1;
        }
        if (acc < 0x80) {
          write_buff ("?3?", 3);
        } else {
          int d = utf8_to_win_char (acc);
          if (d != -1 && d) {
            write_buff_char (d);
          } else {
            write_buff_char ('&');
            write_buff_char ('#');
            write_buff_long (acc);
            write_buff_char (';');
          }
        }
      }
      continue;
    }
    if ((c & 0xc0) == 0xc0) {
      if (st) {
        if (exit_on_error) {
          return -1;
        }
        write_buff ("?4?", 3);
      }
      c -= 0xc0;
      st = 0;
      if (c < 32) {
        acc = c;
        st = 1;
      } else if (c < 48) {
        acc = c - 32;
        st = 2;
      } else if (c < 56) {
        acc = c - 48;
        st = 3;
      } else {
        if (exit_on_error) {
          return -1;
        }
        write_buff ("?5?", 3);
      }
    }
  }
  if (st) {
    if (exit_on_error) {
      return -1;
    }
    write_buff ("?6?", 3);
  }
  return 1;
}