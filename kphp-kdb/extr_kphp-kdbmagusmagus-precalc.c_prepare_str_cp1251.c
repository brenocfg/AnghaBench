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
 int MAX_NAME_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 char* clean_str (char*) ; 
 char* name_buff ; 
 char* prepare_res ; 
 int* prepare_str_UTF8 (char*) ; 
 int /*<<< orphan*/  put_char_utf8 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sp_init () ; 
 char* sp_to_lower (char*) ; 
 char* win_to_utf8_convert ; 

char *prepare_str_cp1251 (char *s, int len) {
  if (len >= MAX_NAME_SIZE / 4 - 1) {
    return NULL;
  }

  sp_init();
  s = sp_to_lower (s);

  int i;
  int state = 0;
  int save_pos = -1;
  int cur_num = 0;
  int name_buff_len = 0;

  for (i = 0; i < len; i++) {
    if (state == 0 && s[i] == '&') {
      save_pos = name_buff_len;
      cur_num = 0;
      state++;
    } else if (state == 1 && s[i] == '#') {
      state++;
    } else if (state == 2 && s[i] >= '0' && s[i] <= '9') {
      if (cur_num < 0x20000) {
        cur_num = s[i] - '0' + cur_num * 10;
      }
    } else if (state == 2 && s[i] == ';') {
      state++;
    } else {
      state = 0;
    }
    if (state == 3 && (cur_num >= 32 && cur_num != 8232 && cur_num != 8233 && cur_num < 0x20000)) {
      name_buff_len = save_pos;
      name_buff[name_buff_len++] = cur_num;
    } else if (state == 3 && cur_num >= 0x10000) {
      name_buff[name_buff_len++] = win_to_utf8_convert[(unsigned char)s[i]];
      name_buff[save_pos] = '$';
    } else {
      name_buff[name_buff_len++] = win_to_utf8_convert[(unsigned char)s[i]];
    }
    if (state == 3) {
      state = 0;
    }
  }
  name_buff[name_buff_len] = 0;

  int *v = prepare_str_UTF8 (name_buff);
  char *t = prepare_res;

  while (*v != 0) {
    t += put_char_utf8 (*v++, t);
  }
  *t++ = 0;
  assert (t - prepare_res < MAX_NAME_SIZE);

  return clean_str (prepare_res);
}