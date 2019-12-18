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
struct roffreq {int dummy; } ;
typedef  struct roffreq ohash ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct roffreq*) ; 
 int /*<<< orphan*/  ohash_delete (struct roffreq*) ; 
 struct roffreq* ohash_first (struct roffreq*,unsigned int*) ; 
 struct roffreq* ohash_next (struct roffreq*,unsigned int*) ; 

void
roffhash_free(struct ohash *htab)
{
	struct roffreq	*req;
	unsigned int	 slot;

	if (htab == NULL)
		return;
	for (req = ohash_first(htab, &slot); req != NULL;
	     req = ohash_next(htab, &slot))
		free(req);
	ohash_delete(htab);
	free(htab);
}