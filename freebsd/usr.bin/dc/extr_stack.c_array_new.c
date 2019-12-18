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
struct array {scalar_t__ size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 struct array* bmalloc (int) ; 

__attribute__((used)) static struct array *
array_new(void)
{
	struct array *a;

	a = bmalloc(sizeof(*a));
	a->data = NULL;
	a->size = 0;
	return a;
}