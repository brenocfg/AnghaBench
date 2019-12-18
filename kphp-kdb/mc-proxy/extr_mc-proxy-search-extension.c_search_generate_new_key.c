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
 scalar_t__ Q_limit ; 
 char const* Q_limit_end ; 
 char const* Q_limit_ptr ; 
 scalar_t__ Q_raw ; 
 scalar_t__ Q_slice_limit ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ sprintf (char*,char*,scalar_t__) ; 

__attribute__((used)) static int search_generate_new_key (char *ptr, const char *key, int len, int pos) {
  int i = pos;
  int w;
  if (Q_slice_limit < Q_limit && key[i] == '#' && Q_limit > 0 && Q_slice_limit > 0 && Q_limit_ptr) {
    i = Q_limit_ptr - key;
    assert ((unsigned) i < 2048);
    memcpy (ptr, key, i);
    i += sprintf (ptr + i, "%d%%", Q_slice_limit);
    w = key + len - Q_limit_end;
    assert ((unsigned) w < 2048);
    memcpy (ptr + i, Q_limit_end, w);
    assert (i + w < len + 3);
    ptr[i+w] = 0;
    return i + w;
  } else if (Q_raw) {
    memcpy (ptr, key, len+1);
    return len;
  } else if (key[i] == '#') {
    memcpy (ptr, key, i+1);
    ptr[i+1] = '%';
    memcpy (ptr+i+2, key+i+1, len-i);
    return len + 1;
  } else {
    memcpy (ptr, key, i);
    ptr[i] = '#';
    ptr[i+1] = '%';
    memcpy (ptr+i+2, key+i, len-i+1);
    return len + 2;
  }
}