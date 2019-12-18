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
struct line {size_t serial; int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int*) ; 
 int* xcalloc (int,int) ; 

__attribute__((used)) static void
unsort(struct line *f, int l, int *b)
{
	int *a, i;

	a = xcalloc(l + 1, sizeof(*a));
	for (i = 1; i <= l; i++)
		a[f[i].serial] = f[i].value;
	for (i = 1; i <= l; i++)
		b[i] = a[i];
	free(a);
}