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
struct vector_read_cmd {size_t size; int* r_container; } ;
typedef  enum read_cmd { ____Placeholder_read_cmd } read_cmd ;

/* Variables and functions */
 int READ_FAIL ; 

__attribute__((used)) static int
vector_read_cmd_find(struct vector_read_cmd *v, enum read_cmd dst)
{
	size_t i;

	if (v == NULL || dst == READ_FAIL)
		return (-1);

	for (i = 0; i < v->size; ++i)
		if (v->r_container[i] == dst)
			return (1);

	return (0);
}