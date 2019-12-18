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
 size_t strspn (char const*,char*) ; 

__attribute__((used)) static int
isDISP(const char *disp)
{
	size_t w;
	int res;

	w = strspn(disp, "0123456789");
	res = 0;
	if (w > 0) {
		if (disp[w] == '\0')
			res = 1;	/* NN */
		else if (disp[w] == '.') {
			disp += w + 1;
			w = strspn(disp, "0123456789");
			if (w > 0 && disp[w] == '\0')
				res = 1;	/* NN.NN */
		}
	}
	return (res);
}