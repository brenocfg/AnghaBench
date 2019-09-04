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
 int /*<<< orphan*/  iseq (char*,char*) ; 
 char* prep_buf_res ; 
 int /*<<< orphan*/  qsort (char**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp_void ; 
 char** words_buf ; 

char *prepare_str_cp1251 (char *v) {
  int i;
  for (i = 0; v[i] == ' '; i++) {
  }

  int k = 0;
  while (v[i]) {
    words_buf[k++] = v + i;
    while (v[i] && v[i] != ' ') {
      i++;
    }
    while (v[i] == ' ') {
      i++;
    }
  }
  v[i] = ' ';

  int j = 0;
  qsort (words_buf, k, sizeof (char *), strcmp_void);

  for (i = 0; i < k; i++) {
    if (i == 0 || !iseq (words_buf[i - 1], words_buf[i])) {
      words_buf[j++] = words_buf[i];
    }
  }
  k = j;

  char *res = prep_buf_res;
  for (i = 0; i < k; i++) {
    char *tmp = words_buf[i];
    while (*tmp != ' ') {
      *res++ = *tmp++;
    }
    *res++ = '+';
  }
  *res++ = 0;

  assert (res - prep_buf_res < MAX_NAME_SIZE);
  return prep_buf_res;
}