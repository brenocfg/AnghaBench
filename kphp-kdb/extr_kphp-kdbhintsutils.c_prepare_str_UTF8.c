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
 int convert_prep (int) ; 
 int /*<<< orphan*/  ispref (int*,int*) ; 
 int* prep_ibuf ; 
 int* prep_ibuf_res ; 
 int /*<<< orphan*/  qsort (int**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stricmp_void ; 
 int** words_ibuf ; 

int *prepare_str_UTF8 (int *x) {
  int *v = prep_ibuf;

  int i, n;
  for (i = 0; x[i]; i++) {
    v[i] = convert_prep (x[i]);
  }

  int j = 0;
//  yo, jo -> e
/*  for (i = 0; v[i]; i++) {
    if ((v[i] == 'y' || v[i] == 'j') && v[i + 1] == 'o') {
      v[j++] = 'e'; i++;
    } else {
      v[j++] = v[i];
    }
  }
  v[j] = 0;
  i = j;
  j = 0;*/

  n = i;
  for (i = 0; v[i] == ' '; i++) {
  }

  int k = 0;
  while (i < n) {
    words_ibuf[k++] = v + i;
    while (v[i] && v[i] != ' ') {
      i++;
    }
    while (v[i] == ' ') {
      i++;
    }
  }
  v[n] = ' ';

  j = 0;
  qsort (words_ibuf, k, sizeof (int *), stricmp_void);

  for (i = 0; i < k; i++) {
    if (i == 0 || !ispref (words_ibuf[j - 1], words_ibuf[i])) {
      words_ibuf[j++] = words_ibuf[i];
    } else {
      words_ibuf[j - 1] = words_ibuf[i];
    }
  }
  k = j;

  int *res = prep_ibuf_res;
  for (i = 0; i < k; i++) {
    int *tmp = words_ibuf[i];
    while (*tmp != ' ') {
      *res++ = *tmp++;
    }
    *res++ = '+';
  }
  *res++ = 0;

  assert (res - prep_ibuf_res < MAX_NAME_SIZE);
  return prep_ibuf_res;
}