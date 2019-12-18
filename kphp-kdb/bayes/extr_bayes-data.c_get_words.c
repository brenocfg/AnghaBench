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
typedef  int /*<<< orphan*/  ll ;

/* Variables and functions */
 int MAX_WORDS ; 
 int /*<<< orphan*/  add_kludge (int,int) ; 
 int /*<<< orphan*/  add_word (scalar_t__*) ; 
 int /*<<< orphan*/  bayes_string_to_utf8 (unsigned char*,scalar_t__*) ; 
 scalar_t__ binlog_readed ; 
 char* buf_debug ; 
 int /*<<< orphan*/  cmp_ll ; 
 int /*<<< orphan*/  correct_lang (scalar_t__*) ; 
 int delete_links () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_type_case (scalar_t__) ; 
 int get_type_lang (scalar_t__) ; 
 scalar_t__ is_letter (scalar_t__) ; 
 int /*<<< orphan*/  put_string_utf8 (scalar_t__*,char*) ; 
 int /*<<< orphan*/  qsort (scalar_t__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 scalar_t__* v ; 
 int verbosity ; 
 scalar_t__* words ; 
 int words_len ; 

int get_words (char *s) {
  if (verbosity > 2 && binlog_readed) {
    fprintf (stderr, "in get words\n");
  }

  words_len = 0;
  int i;

  if (strlen (s) + 1 > MAX_WORDS) {
    s[MAX_WORDS - 1] = 0;
  }

  for (i = strlen (s); i > 0 && s[i - 1] != '\t'; i--) ;

  bayes_string_to_utf8 ((unsigned char *)(s + i), v);
  s = NULL;

  if (verbosity > 1 && binlog_readed) {
    put_string_utf8 (v, buf_debug);
    fprintf (stderr, "bayes_get_words: %s\n", buf_debug);
  }

  int result = delete_links();

  int cur_mixed_lang = 0;
  for (i = 0; v[i] && v[i + 1] && cur_mixed_lang < 25; i++) {
    if ((get_type_lang (v[i]) + get_type_lang (v[i + 1]) == 1)) {
      if (!correct_lang (&v[i]) && !correct_lang (&v[i + 1])) {
        add_kludge (0, cur_mixed_lang++);
        while (get_type_lang (v[i + 1]) != 2) {
          i++;
        }
      }
    }
  }

  int cur_mixed_case = 0;
  for (i = 0; v[i] && v[i + 1] && cur_mixed_case < 25; i++) {
//    if (get_type_case (v[i]) == 0 && get_type_case (v[i + 1]) == 1 && ((i != 0 && is_letter (v[i - 1])) || is_letter (v[i + 2]))) {
    if (get_type_case (v[i]) == 0 && get_type_case (v[i + 1]) == 1 && get_type_case (v[i + 2]) == 1) {
      add_kludge (1, cur_mixed_case++);
    }
  }

  int cur_len = -words_len;
  int j = 0, t;
  while (v[j]) {
    while (v[j] && !is_letter (v[j])) {
      j++;
    }
    if (v[j]) {
      i = j;
      while (v[i] && is_letter (v[i])) {
        i++;
      }

      if (v[i]) {
        t = i + 1;
        v[i] = 0;
      } else {
        t = i;
      }

      if (i - j > 2) {
        add_word (&v[j]);
      }
      j = t;
    }
  }

  cur_len += words_len;
  if (cur_len >= 11) {
    cur_len = (cur_len - 11)/ 4 + 11;
  }

  if (cur_len > 25) {
    cur_len = 25;
  }

  add_kludge (2, cur_len);

  qsort (words, words_len, sizeof (ll), cmp_ll);
  j = 1;
  for (i = 1; i < words_len; i++)
    if (words[i] != words[i - 1])
      words[j++] = words[i];
  words_len = j;

  words[words_len] = 0;

  if (verbosity > 2 && binlog_readed) {
    fprintf (stderr, "go out get words\n");
  }

  return result;
}