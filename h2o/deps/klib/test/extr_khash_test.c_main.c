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
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  data_size ; 
 int /*<<< orphan*/  ht_destroy_data () ; 
 int /*<<< orphan*/  ht_init_data () ; 
 int /*<<< orphan*/  ht_khash_int ; 
 int /*<<< orphan*/  ht_khash_packed ; 
 int /*<<< orphan*/  ht_khash_str ; 
 int /*<<< orphan*/  ht_khash_unpack ; 
 int /*<<< orphan*/  ht_timing (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	if (argc > 1) data_size = atoi(argv[1]);
	ht_init_data();
	ht_timing(ht_khash_int);
	ht_timing(ht_khash_str);
	ht_timing(ht_khash_unpack);
	ht_timing(ht_khash_packed);
	ht_destroy_data();
	return 0;
}