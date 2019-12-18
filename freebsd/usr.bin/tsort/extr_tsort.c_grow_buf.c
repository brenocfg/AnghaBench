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

/* Variables and functions */
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 void* realloc (void*,size_t) ; 

__attribute__((used)) static void *
grow_buf(void *bp, size_t size)
{
	if ((bp = realloc(bp, size)) == NULL)
		err(1, NULL);
	return (bp);
}