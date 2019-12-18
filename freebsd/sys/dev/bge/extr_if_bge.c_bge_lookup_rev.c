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
typedef  scalar_t__ uint32_t ;
struct bge_revision {scalar_t__ br_chipid; int /*<<< orphan*/ * br_name; } ;

/* Variables and functions */
 scalar_t__ BGE_ASICREV (scalar_t__) ; 
 struct bge_revision* bge_majorrevs ; 
 struct bge_revision* bge_revisions ; 

__attribute__((used)) static const struct bge_revision *
bge_lookup_rev(uint32_t chipid)
{
	const struct bge_revision *br;

	for (br = bge_revisions; br->br_name != NULL; br++) {
		if (br->br_chipid == chipid)
			return (br);
	}

	for (br = bge_majorrevs; br->br_name != NULL; br++) {
		if (br->br_chipid == BGE_ASICREV(chipid))
			return (br);
	}

	return (NULL);
}