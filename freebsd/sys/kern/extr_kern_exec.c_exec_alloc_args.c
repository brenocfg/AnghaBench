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
struct image_args {char* buf; int /*<<< orphan*/  bufkva; } ;

/* Variables and functions */
 scalar_t__ exec_alloc_args_kva (int /*<<< orphan*/ *) ; 

int
exec_alloc_args(struct image_args *args)
{

	args->buf = (char *)exec_alloc_args_kva(&args->bufkva);
	return (0);
}