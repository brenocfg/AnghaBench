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
 int data_size ; 
 int h ; 
 int /*<<< orphan*/  kh_del (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  kh_destroy (int /*<<< orphan*/ ,int) ; 
 int kh_init (int /*<<< orphan*/ ) ; 
 unsigned int kh_put (int /*<<< orphan*/ ,int,char*,int*) ; 
 int kh_size (int) ; 
 int khash_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  str ; 
 char** str_data ; 

void ht_khash_str()
{
	int i, ret;
	char **data = str_data;
	khash_t(str) *h;
	unsigned k;

	h = kh_init(str);
	for (i = 0; i < data_size; ++i) {
		k = kh_put(str, h, data[i], &ret);
		if (!ret) kh_del(str, h, k);
	}
	printf("[ht_khash_int] size: %u\n", kh_size(h));
	kh_destroy(str, h);
}