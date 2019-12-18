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
typedef  int /*<<< orphan*/  m_pool_s ;

/* Variables and functions */
 int DEBUG_ALLOC ; 
 int DEBUG_FLAGS ; 
 int MEMO_WARN ; 
 void* ___sym_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,...) ; 

__attribute__((used)) static void *__sym_calloc2(m_pool_s *mp, int size, char *name, int uflags)
{
	void *p;

	p = ___sym_malloc(mp, size);

	if (DEBUG_FLAGS & DEBUG_ALLOC)
		printf ("new %-10s[%4d] @%p.\n", name, size, p);

	if (p)
		bzero(p, size);
	else if (uflags & MEMO_WARN)
		printf ("__sym_calloc2: failed to allocate %s[%d]\n", name, size);

	return p;
}