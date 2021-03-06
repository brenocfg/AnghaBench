#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int key; int val; } ;
typedef  TYPE_1__ int_packed_t ;

/* Variables and functions */
 int data_size ; 
 int h ; 
 unsigned int* int_data ; 
 int /*<<< orphan*/  ipk ; 
 int /*<<< orphan*/  kh_del (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  kh_destroy (int /*<<< orphan*/ ,int) ; 
 int kh_init (int /*<<< orphan*/ ) ; 
 unsigned int kh_put (int /*<<< orphan*/ ,int,TYPE_1__,int*) ; 
 int kh_size (int) ; 
 int khash_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void ht_khash_packed()
{
	int i, ret;
	unsigned *data = int_data;
	khash_t(ipk) *h;
	unsigned k;

	h = kh_init(ipk);
	for (i = 0; i < data_size; ++i) {
		int_packed_t x;
		x.key = data[i]; x.val = i&0xff;
		k = kh_put(ipk, h, x, &ret);
		if (!ret) kh_del(ipk, h, k);
	}
	printf("[ht_khash_packed] size: %u (sizeof=%ld)\n", kh_size(h), sizeof(int_packed_t));
	kh_destroy(ipk, h);
}