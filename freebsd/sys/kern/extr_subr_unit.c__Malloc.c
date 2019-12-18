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
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 void* calloc (size_t,int) ; 
 scalar_t__ no_alloc ; 

__attribute__((used)) static void *
_Malloc(size_t foo, int line)
{

	KASSERT(no_alloc == 0, ("malloc in wrong place() line %d", line));
	return (calloc(foo, 1));
}