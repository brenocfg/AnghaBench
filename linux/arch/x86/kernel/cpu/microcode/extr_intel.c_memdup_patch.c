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
struct ucode_patch {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ucode_patch*) ; 
 int /*<<< orphan*/  kmemdup (void*,unsigned int,int /*<<< orphan*/ ) ; 
 struct ucode_patch* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ucode_patch *memdup_patch(void *data, unsigned int size)
{
	struct ucode_patch *p;

	p = kzalloc(sizeof(struct ucode_patch), GFP_KERNEL);
	if (!p)
		return NULL;

	p->data = kmemdup(data, size, GFP_KERNEL);
	if (!p->data) {
		kfree(p);
		return NULL;
	}

	return p;
}