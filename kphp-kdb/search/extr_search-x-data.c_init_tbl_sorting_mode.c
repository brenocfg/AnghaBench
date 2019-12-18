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
 int FLAG_REVERSE_SEARCH ; 
 int /*<<< orphan*/  assert (int) ; 
 char* rate_first_characters ; 
 int* tbl_sorting_mode ; 

__attribute__((used)) static void init_tbl_sorting_mode () {
  const char *p = rate_first_characters;
  int i;
  for (i = 0; i < 128; i++) {
    tbl_sorting_mode[i] = -1;
  }
/*
  assert (strchr(rate_first_characters, 'i') == 0);
  tbl_sorting_mode['i'] = MAX_RATES;
  tbl_sorting_mode['I'] = MAX_RATES | FLAG_REVERSE_SEARCH;
*/
  i = 0;
  while (*p) {
    assert ('a' <= *p && *p <= 'z');
    tbl_sorting_mode[(int) *p] = i;
    tbl_sorting_mode[(int) (*p - 32)] = i | FLAG_REVERSE_SEARCH;
    i++;
    p++;
  }
}