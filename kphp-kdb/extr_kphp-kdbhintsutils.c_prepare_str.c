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
 char* dl_malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* prep_buf ; 
 int /*<<< orphan*/  prep_ibuf ; 
 int* prepare_str_UTF8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_char_utf8 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_to_utf8 (unsigned char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

char *prepare_str (char *x) {
  if (strlen (x) >= MAX_NAME_SIZE / 4) {
    return NULL;
  }

  string_to_utf8 ((unsigned char *)x, prep_ibuf);
  int *v = prepare_str_UTF8 (prep_ibuf);
  char *s = prep_buf;

  while (*v != 0) {
    s += put_char_utf8 (*v++, s);
  }
  *s++ = 0;

  assert (s - prep_buf < MAX_NAME_SIZE);

  char *res = dl_malloc (s - prep_buf);
  if (res == NULL) {
    return res;
  }

  memcpy (res, prep_buf, s - prep_buf);
  return res;
}