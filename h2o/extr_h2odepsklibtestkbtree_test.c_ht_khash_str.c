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
 int /*<<< orphan*/  KB_DEFAULT_SIZE ; 
 int /*<<< orphan*/  __kb_destroy (int) ; 
 int data_size ; 
 int h ; 
 int /*<<< orphan*/  kb_del (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ kb_get (int /*<<< orphan*/ ,int,char*) ; 
 int kb_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kb_put (int /*<<< orphan*/ ,int,char*) ; 
 int kb_size (int) ; 
 int kbtree_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  str ; 
 char** str_data ; 

void ht_khash_str()
{
	int i;
	char **data = str_data;
	kbtree_t(str) *h;

	h = kb_init(str, KB_DEFAULT_SIZE);
	for (i = 0; i < data_size; ++i) {
		if (kb_get(str, h, data[i]) == 0) kb_put(str, h, data[i]);
		else kb_del(str, h, data[i]);
	}
	printf("[ht_khash_int] size: %d\n", kb_size(h));
	__kb_destroy(h);
}