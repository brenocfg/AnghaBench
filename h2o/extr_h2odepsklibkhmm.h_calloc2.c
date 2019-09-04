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
 scalar_t__ malloc (int) ; 

__attribute__((used)) static inline void **calloc2(int n_row, int n_col, int size)
{
	char **p;
	int k;
	p = (char**)malloc(sizeof(char*) * n_row);
	for (k = 0; k != n_row; ++k)
		p[k] = (char*)calloc(n_col, size);
	return (void**)p;
}