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
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int /*<<< orphan*/  advance_write_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 char* get_write_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int return_one_key (struct connection*,char const*,char*,int) ; 
 size_t sprintf (char*,char*,int const) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char const*,int) ; 

int return_one_key_list (struct connection *c, const char *key, int key_len, int res, int mode, const int *R, int R_cnt) {
  int w, i;
  static char buff[16];

  if (verbosity > 0) {
    fprintf (stderr, "result = %d\n", res);
  }

  if (!R_cnt) {
    if (res == 0x7fffffff) {
      return return_one_key (c, key, "", 0);
    }
    if (mode < 0) {
      w = 4;
      *((int *) buff) = res;
    } else {
      w = sprintf (buff, "%d", res);
    }
    return return_one_key (c, key, buff, w);
  }

  write_out (&c->Out, "VALUE ", 6);
  write_out (&c->Out, key, key_len);

  char *ptr = get_write_ptr (&c->Out, 512);
  if (!ptr) return -1;
  char *s = ptr + 480;

  memcpy (ptr, " 0 .........\r\n", 14);
  char *size_ptr = ptr + 3;

  ptr += 14;
  if (res != 0x7fffffff) {
    if (mode >= 0) {
      w = sprintf (ptr, "%d", res);
    } else {
      w = 4;
      *((int *) ptr) = res;
    }
    ptr += w;
  } else {
    w = 0;
  }

  for (i = 0; i < R_cnt; i++) {
    int t;
    if (ptr >= s) {
      advance_write_ptr (&c->Out, ptr - (s - 480));
      ptr = get_write_ptr (&c->Out, 512);
      if (!ptr) return -1;
      s = ptr + 480;
    }
    if (mode >= 0) {
      if (i || res != 0x7fffffff) {
        *ptr++ = ',';  w++;
      }
      w += t = sprintf (ptr, "%d", R[i]);
    } else {
      w += t = 4;
      *((int *) ptr) = R[i];
    }
    ptr += t;
  }
  size_ptr[sprintf (size_ptr, "% 9d", w)] = '\r';
  memcpy (ptr, "\r\n", 2);
  ptr += 2;
  advance_write_ptr (&c->Out, ptr - (s - 480));

  return 0;
}