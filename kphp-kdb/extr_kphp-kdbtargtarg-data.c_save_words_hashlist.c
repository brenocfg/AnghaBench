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
typedef  int /*<<< orphan*/  hash_list_t ;

/* Variables and functions */
 int /*<<< orphan*/ * save_words_hashlist_pattern (char const*,int,int,int /*<<< orphan*/ ,int) ; 

inline hash_list_t *save_words_hashlist (const char *str, int flags, int type) {
  return save_words_hashlist_pattern (str, flags, -1, 0, type);
}