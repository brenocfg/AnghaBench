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
 int eat_at (char const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int mct_get ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int verbosity ; 

int hints_merge_check_query (int type, const char *key, int key_len) {
  if (type != mct_get) {
    return 0;
  }
  
  if (verbosity > 2) {
    fprintf (stderr, "hints_merge_check_query (key = %s)\n", key);
  }

  int l = eat_at (key, key_len);
  key += l;
  key_len -= l;
  
  return (key_len > 12 && !strncmp (key, "gather_hints", 12));
}