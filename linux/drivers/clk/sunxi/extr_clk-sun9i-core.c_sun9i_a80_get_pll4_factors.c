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
struct factors_request {int rate; int n; int m; int p; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static void sun9i_a80_get_pll4_factors(struct factors_request *req)
{
	int n;
	int m = 1;
	int p = 1;

	/* Normalize value to a 6 MHz multiple (24 MHz / 4) */
	n = DIV_ROUND_UP(req->rate, 6000000);

	/* If n is too large switch to steps of 12 MHz */
	if (n > 255) {
		m = 0;
		n = (n + 1) / 2;
	}

	/* If n is still too large switch to steps of 24 MHz */
	if (n > 255) {
		p = 0;
		n = (n + 1) / 2;
	}

	/* n must be between 12 and 255 */
	if (n > 255)
		n = 255;
	else if (n < 12)
		n = 12;

	req->rate = ((24000000 * n) >> p) / (m + 1);
	req->n = n;
	req->m = m;
	req->p = p;
}