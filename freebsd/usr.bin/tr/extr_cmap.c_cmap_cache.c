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
struct cmap {int cm_havecache; int /*<<< orphan*/ * cm_cache; } ;

/* Variables and functions */
 size_t CM_CACHE_SIZE ; 
 int /*<<< orphan*/  cmap_lookup_hard (struct cmap*,size_t) ; 

void
cmap_cache(struct cmap *cm)
{
	wint_t ch;

	for (ch = 0; ch < CM_CACHE_SIZE; ch++)
		cm->cm_cache[ch] = cmap_lookup_hard(cm, ch);

	cm->cm_havecache = true;
}