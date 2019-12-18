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
typedef  int ll ;

/* Variables and functions */
 int HASH_MUL ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  debugp (char*,char*,long long) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  put_string_utf8 (int*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int* words ; 
 int /*<<< orphan*/  words_len ; 

void add_word (int *v) {
//TODO: remove useless put_sting_utf8

  char tmp[10000];
  put_string_utf8 (v, tmp);

  if (debug) {
    fprintf (stderr, "WORD %s\n", tmp);
  }

  ll res = 0;
  while (*v) {
    res = (res * HASH_MUL) + *v++;
  }

  debugp ("WORD %s | %lld\n", tmp, (long long)((ll)res));

  words[words_len++] = res;
}