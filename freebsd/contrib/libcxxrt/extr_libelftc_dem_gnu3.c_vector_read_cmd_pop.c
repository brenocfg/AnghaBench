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
struct vector_read_cmd {size_t size; int /*<<< orphan*/ * r_container; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_FAIL ; 

__attribute__((used)) static int
vector_read_cmd_pop(struct vector_read_cmd *v)
{

	if (v == NULL || v->size == 0)
		return (0);

	--v->size;
	v->r_container[v->size] = READ_FAIL;

	return (1);
}