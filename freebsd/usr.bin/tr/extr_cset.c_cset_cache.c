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
typedef  size_t wchar_t ;
struct cset {int cs_havecache; int /*<<< orphan*/ * cs_cache; } ;

/* Variables and functions */
 size_t CS_CACHE_SIZE ; 
 int /*<<< orphan*/  cset_in_hard (struct cset*,size_t) ; 

void
cset_cache(struct cset *cs)
{
	wchar_t i;

	for (i = 0; i < CS_CACHE_SIZE; i++)
		cs->cs_cache[i] = cset_in_hard(cs, i);

	cs->cs_havecache = true;
}