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
 int /*<<< orphan*/  SEARCHX_EXTENSION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int eat_at (char const*,int) ; 
 int mct_get ; 
 scalar_t__ search_check_query (int,char const*,int) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

int searchx_check_query (int type, const char *key, int key_len) {
  if (type != mct_get) {
    return 0;
  }

  int l =  eat_at (key, key_len);
  key += l;
  key_len -= l;

  assert (SEARCHX_EXTENSION);

  return (key_len >= 7 && !strncmp (key, "searchx", 7)) || (key_len >= 7 && !strncmp (key, "searchu", 7)) || search_check_query (type, key, key_len);
}