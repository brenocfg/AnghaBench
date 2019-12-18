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
struct entry {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  hash_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline void cache_assign_hash_entry ( struct entry *entry) {
  entry->hash_entry = get_entry (entry->key, entry->key_len);
}