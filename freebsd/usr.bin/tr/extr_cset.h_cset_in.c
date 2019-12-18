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
struct cset {int* cs_cache; scalar_t__ cs_havecache; } ;

/* Variables and functions */
 size_t CS_CACHE_SIZE ; 
 int cset_in_hard (struct cset*,size_t) ; 

__attribute__((used)) static __inline bool
cset_in(struct cset *cs, wchar_t ch)
{

	if (ch < CS_CACHE_SIZE && cs->cs_havecache)
		return (cs->cs_cache[ch]);
	return (cset_in_hard(cs, ch));
}