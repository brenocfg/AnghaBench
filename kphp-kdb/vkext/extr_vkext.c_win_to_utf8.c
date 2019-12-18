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
 int cur_buff_len ; 
 int* win_to_utf8_convert ; 
 int /*<<< orphan*/  write_buff_char_pos (char,int) ; 
 int write_buff_get_pos () ; 
 int /*<<< orphan*/  write_buff_set_pos (int) ; 
 int /*<<< orphan*/  write_char_utf8 (int) ; 

int win_to_utf8 (const char *s, int len) {
  int i;
  int state = 0;
  int save_pos = -1;
  int cur_num = 0;
  for (i = 0; i < len; i++) {
    if (state == 0 && s[i] == '&') {
      save_pos = write_buff_get_pos ();
      cur_num = 0;
      state ++;
    } else if (state == 1 && s[i] == '#') {
      state ++;
    } else if (state == 2 && s[i] >= '0' && s[i] <= '9') {
      if (cur_num < 0x20000) {
        cur_num = s[i] - '0' + cur_num * 10;
      }
    } else if (state == 2 && s[i] == ';') {
      state ++;
    } else {
      state = 0;
    }
    if (state == 3 && (cur_num >= 32 && cur_num != 33 && cur_num != 34 && cur_num != 36 && cur_num != 39 && cur_num != 60 && cur_num != 62 && cur_num != 92 && cur_num != 8232 && cur_num != 8233 && cur_num < 0x20000)) {
      write_buff_set_pos (save_pos);
      assert (save_pos == write_buff_get_pos ());
      write_char_utf8 (cur_num);
    } else if (state == 3 && cur_num >= 0x10000) {
      write_char_utf8 (win_to_utf8_convert[(unsigned char)(s[i])]);
      write_buff_char_pos ('$', save_pos);
    } else {
      write_char_utf8 (win_to_utf8_convert[(unsigned char)(s[i])]);
    }
    if (state == 3) {      
      state = 0;
    }
  }
  return cur_buff_len;
}