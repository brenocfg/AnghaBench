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
struct index_entry {int /*<<< orphan*/  key_len; int /*<<< orphan*/  data; } ;
struct hash_entry {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int mystrcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int key_cmp (struct hash_entry *a, struct index_entry *b) {
  if (a == 0) return 1;
  if (b == 0) return -1;
  return mystrcmp(a->key, a->key_len, b->data, b->key_len);
}