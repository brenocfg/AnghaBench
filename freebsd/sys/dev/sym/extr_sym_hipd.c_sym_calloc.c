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
 void* __sym_calloc (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  mp0 ; 

__attribute__((used)) static void *sym_calloc(int size, char *name)
{
	void *m;
	/* Lock */
	m = __sym_calloc(&mp0, size, name);
	/* Unlock */
	return m;
}