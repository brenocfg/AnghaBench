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

/* Variables and functions */
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  r_sort_a (int /*<<< orphan*/  const**,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int
radixsort(const u_char **a, int n, const u_char *tab, u_int endch)
{
	const u_char *tr;
	int c;
	u_char tr0[256];

	SETUP;
	r_sort_a(a, n, 0, tr, endch);
	return (0);
}