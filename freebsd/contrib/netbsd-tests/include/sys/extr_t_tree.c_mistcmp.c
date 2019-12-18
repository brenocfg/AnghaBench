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
struct mist {int key; } ;

/* Variables and functions */

__attribute__((used)) static int
mistcmp(struct mist *a, struct mist *b)
{
#if 0
	return (b->key - a->key); /* wrong, can overflow */
#else
	if (b->key > a->key)
		return 1;
	else if (b->key < a->key)
		return (-1);
	else
		return 0;
#endif
}