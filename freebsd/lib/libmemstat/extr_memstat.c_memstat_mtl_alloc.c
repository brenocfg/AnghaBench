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
struct memory_type_list {int /*<<< orphan*/  mtl_error; int /*<<< orphan*/  mtl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEMSTAT_ERROR_UNDEFINED ; 
 struct memory_type_list* malloc (int) ; 

struct memory_type_list *
memstat_mtl_alloc(void)
{
	struct memory_type_list *mtlp;

	mtlp = malloc(sizeof(*mtlp));
	if (mtlp == NULL)
		return (NULL);

	LIST_INIT(&mtlp->mtl_list);
	mtlp->mtl_error = MEMSTAT_ERROR_UNDEFINED;
	return (mtlp);
}