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
 int conv_rus_utf8 (int) ; 
 int maxn ; 
 int /*<<< orphan*/  put_string_utf8 (int*,char*) ; 
 int stem_rus (int,int) ; 
 int* stem_ts ; 
 int* stem_ts_v ; 
 int /*<<< orphan*/  string_to_utf8 (unsigned char*,int*) ; 

int stem_rus_utf8 (const char *s, char *res, int use_dictionary) {
  int i;
  string_to_utf8 ((unsigned char *)s, stem_ts_v);
  for (i = 0; stem_ts[i] && i + 100 < maxn; i++) {
    stem_ts[i] = conv_rus_utf8 (stem_ts_v[i]);
  }
  int l = stem_rus (i, use_dictionary);
  for (i = 0; i < l; i++) {
    if (stem_ts[i] != 32) {
      stem_ts_v[i] = stem_ts[i] + 1072;
    }
  }
  stem_ts_v[l] = 0;
  put_string_utf8 (stem_ts_v, res);
  return l;
}