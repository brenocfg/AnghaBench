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
struct asymmetric_key_ids {struct asymmetric_key_ids** id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct asymmetric_key_ids**) ; 
 int /*<<< orphan*/  kfree (struct asymmetric_key_ids*) ; 

__attribute__((used)) static void asymmetric_key_free_kids(struct asymmetric_key_ids *kids)
{
	int i;

	if (kids) {
		for (i = 0; i < ARRAY_SIZE(kids->id); i++)
			kfree(kids->id[i]);
		kfree(kids);
	}
}