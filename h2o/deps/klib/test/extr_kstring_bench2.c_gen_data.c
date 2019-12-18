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
 int drand48 () ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  srand48 (int) ; 
 int str_len ; 

char *gen_data(int len, int a)
{
	char *data;
	int i;
	long x;
	srand48(11);
	data = malloc(len);
	for (i = 0; i < len; ++i)
		data[i] = (int)(a * drand48()) + '!';
	data[str_len - 1] = 0;
	return data;
}