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
typedef  int /*<<< orphan*/  uint32_t ;
struct mandoc_xr {char* sec; char* hashkey; char* name; int line; int pos; int count; struct mandoc_xr* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mandoc_xr*) ; 
 struct mandoc_xr* mandoc_malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 struct mandoc_xr* ohash_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ohash_insert (int /*<<< orphan*/ *,unsigned int,struct mandoc_xr*) ; 
 int /*<<< orphan*/  ohash_interval (char*,char const**) ; 
 unsigned int ohash_lookup_memory (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 struct mandoc_xr* xr_first ; 
 int /*<<< orphan*/ * xr_hash ; 
 struct mandoc_xr* xr_last ; 

int
mandoc_xr_add(const char *sec, const char *name, int line, int pos)
{
	struct mandoc_xr	 *xr, *oxr;
	const char		 *pend;
	size_t			  ssz, nsz, tsz;
	unsigned int		  slot;
	int			  ret;
	uint32_t		  hv;

	if (xr_hash == NULL)
		return 0;

	ssz = strlen(sec) + 1;
	nsz = strlen(name) + 1;
	tsz = ssz + nsz;
	xr = mandoc_malloc(sizeof(*xr) + tsz);
	xr->next = NULL;
	xr->sec = xr->hashkey;
	xr->name = xr->hashkey + ssz;
	xr->line = line;
	xr->pos = pos;
	xr->count = 1;
	memcpy(xr->sec, sec, ssz);
	memcpy(xr->name, name, nsz);

	pend = xr->hashkey + tsz;
	hv = ohash_interval(xr->hashkey, &pend);
	slot = ohash_lookup_memory(xr_hash, xr->hashkey, tsz, hv);
	if ((oxr = ohash_find(xr_hash, slot)) == NULL) {
		ohash_insert(xr_hash, slot, xr);
		if (xr_first == NULL)
			xr_first = xr;
		else
			xr_last->next = xr;
		xr_last = xr;
		return 0;
	}

	oxr->count++;
	ret = (oxr->line == -1) ^ (xr->line == -1);
	if (xr->line == -1)
		oxr->line = -1;
	free(xr);
	return ret;
}