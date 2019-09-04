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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 char* trans_letter (char*,int*) ; 

char *translit_str (char *buffer, int buff_size, char *str, int len) {
  char *ptr = str, *out = buffer, *str_e = str + len, *out_e = buffer + buff_size;
  while (ptr < str_e && *ptr) {
    int a = 0, b;
    char *tr = trans_letter (ptr, &a);
    if (tr) {
      b = strlen (tr);
    } else {
      b = 1;
      tr = ptr;
    }
    assert (a > 0 && b >= 0);
    if (out + b > out_e) {
      *out = 0;
      return buffer;
    }
    memcpy (out, tr, b);
    out += b;
    ptr += a;
  }
  *out = 0;
  return buffer;    
}