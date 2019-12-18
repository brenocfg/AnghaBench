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
struct dba_array {int flags; scalar_t__ pos; scalar_t__ ec; scalar_t__ ed; scalar_t__ eu; scalar_t__ ea; void* em; void* ep; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct dba_array* mandoc_malloc (int) ; 
 void* mandoc_reallocarray (int /*<<< orphan*/ *,scalar_t__,int) ; 

struct dba_array *
dba_array_new(int32_t ea, int flags)
{
	struct dba_array	*array;

	assert(ea > 0);
	array = mandoc_malloc(sizeof(*array));
	array->ep = mandoc_reallocarray(NULL, ea, sizeof(*array->ep));
	array->em = mandoc_reallocarray(NULL, ea, sizeof(*array->em));
	array->ea = ea;
	array->eu = 0;
	array->ed = 0;
	array->ec = 0;
	array->flags = flags;
	array->pos = 0;
	return array;
}