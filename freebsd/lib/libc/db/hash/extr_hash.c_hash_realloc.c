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
typedef  int /*<<< orphan*/  SEGMENT ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memmove (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *
hash_realloc(SEGMENT **p_ptr, int oldsize, int newsize)
{
	void *p;

	if ( (p = malloc(newsize)) ) {
		memmove(p, *p_ptr, oldsize);
		memset((char *)p + oldsize, 0, newsize - oldsize);
		free(*p_ptr);
		*p_ptr = p;
	}
	return (p);
}