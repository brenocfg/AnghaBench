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
struct key_tok {scalar_t__ token; } ;

/* Variables and functions */

int
compare_key_tok_id(
	const void *a1,
	const void *a2
	)
{
	const struct key_tok *p1 = a1;
	const struct key_tok *p2 = a2;

	if (p1->token == p2->token)
		return 0;

	if (p1->token < p2->token)
		return -1;
	else
		return 1;
}