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
 scalar_t__ calloc (int,int) ; 
 int data_size ; 
 int drand48 () ; 
 int* int_data ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  srand48 (int) ; 
 char** str_data ; 
 char* strdup (char*) ; 

void ht_init_data()
{
	int i;
	char buf[256];
	printf("--- generating data... ");
	srand48(11);
	int_data = (unsigned*)calloc(data_size, sizeof(unsigned));
	str_data = (char**)calloc(data_size, sizeof(char*));
	for (i = 0; i < data_size; ++i) {
		int_data[i] = (unsigned)(data_size * drand48() / 4) * 271828183u;
		sprintf(buf, "%x", int_data[i]);
		str_data[i] = strdup(buf);
	}
	printf("done!\n");
}