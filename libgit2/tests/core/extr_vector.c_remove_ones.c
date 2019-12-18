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
typedef  int /*<<< orphan*/  git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 void* git_vector_get (int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int remove_ones(const git_vector *v, size_t idx, void *p)
{
	GIT_UNUSED(p);
	return (git_vector_get(v, idx) == (void *)0x001);
}