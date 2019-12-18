#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct packing_data {struct object_entry* ext_bases; scalar_t__ nr_ext; int /*<<< orphan*/  alloc_ext; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct TYPE_4__ {TYPE_1__ oid; } ;
struct object_entry {int preferred_base; int filled; int ext_base; int delta_idx; TYPE_2__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct object_entry*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  memset (struct object_entry*,int /*<<< orphan*/ ,int) ; 

void oe_set_delta_ext(struct packing_data *pdata,
		      struct object_entry *delta,
		      const unsigned char *sha1)
{
	struct object_entry *base;

	ALLOC_GROW(pdata->ext_bases, pdata->nr_ext + 1, pdata->alloc_ext);
	base = &pdata->ext_bases[pdata->nr_ext++];
	memset(base, 0, sizeof(*base));
	hashcpy(base->idx.oid.hash, sha1);

	/* These flags mark that we are not part of the actual pack output. */
	base->preferred_base = 1;
	base->filled = 1;

	delta->ext_base = 1;
	delta->delta_idx = base - pdata->ext_bases + 1;
}