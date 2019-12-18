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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int /*<<< orphan*/  SETUP ; 
 int THRESHOLD ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ ** malloc (int) ; 
 int /*<<< orphan*/  r_sort_b (int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplesort (int /*<<< orphan*/  const**,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int
sradixsort(const u_char **a, int n, const u_char *tab, u_int endch)
{
	const u_char *tr, **ta;
	int c;
	u_char tr0[256];

	SETUP;
	if (n < THRESHOLD)
		simplesort(a, n, 0, tr, endch);
	else {
		if ((ta = malloc(n * sizeof(a))) == NULL)
			return (-1);
		r_sort_b(a, ta, n, 0, tr, endch);
		free(ta);
	}
	return (0);
}