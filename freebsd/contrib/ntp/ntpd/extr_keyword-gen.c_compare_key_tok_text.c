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
struct key_tok {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
compare_key_tok_text(
	const void *a1,
	const void *a2
	)
{
	const struct key_tok *p1 = a1;
	const struct key_tok *p2 = a2;

	return strcmp(p1->key, p2->key);
}