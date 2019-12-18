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
struct proto_md {int /*<<< orphan*/  bd_tag; int /*<<< orphan*/  bd_map; int /*<<< orphan*/ * virtaddr; scalar_t__ physaddr; } ;
struct proto_busdma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct proto_md*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PROTO_BUSDMA ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct proto_md*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mds ; 
 int /*<<< orphan*/  peers ; 

__attribute__((used)) static int
proto_busdma_md_destroy_internal(struct proto_busdma *busdma,
    struct proto_md *md)
{

	LIST_REMOVE(md, mds);
	LIST_REMOVE(md, peers);
	if (md->physaddr)
		bus_dmamap_unload(md->bd_tag, md->bd_map);
	if (md->virtaddr != NULL)
		bus_dmamem_free(md->bd_tag, md->virtaddr, md->bd_map);
	else
		bus_dmamap_destroy(md->bd_tag, md->bd_map);
	bus_dma_tag_destroy(md->bd_tag);
	free(md, M_PROTO_BUSDMA);
	return (0);
}