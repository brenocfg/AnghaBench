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
typedef  size_t wint_t ;
struct cmap {size_t* cm_cache; scalar_t__ cm_havecache; } ;

/* Variables and functions */
 size_t CM_CACHE_SIZE ; 
 size_t cmap_lookup_hard (struct cmap*,size_t) ; 

__attribute__((used)) static __inline wint_t
cmap_lookup(struct cmap *cm, wint_t from)
{

	if (from < CM_CACHE_SIZE && cm->cm_havecache)
		return (cm->cm_cache[from]);
	return (cmap_lookup_hard(cm, from));
}