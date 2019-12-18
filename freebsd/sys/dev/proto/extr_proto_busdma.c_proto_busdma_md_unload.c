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
struct proto_md {scalar_t__ physaddr; int /*<<< orphan*/  bd_map; int /*<<< orphan*/  bd_tag; } ;
struct proto_busdma {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
proto_busdma_md_unload(struct proto_busdma *busdma, struct proto_md *md)
{

	if (!md->physaddr)
		return (ENXIO);
	bus_dmamap_unload(md->bd_tag, md->bd_map);
	md->physaddr = 0;
	return (0);
}