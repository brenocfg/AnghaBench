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
struct proto_tag {int /*<<< orphan*/  mds; int /*<<< orphan*/  maxsegsz; int /*<<< orphan*/  nsegs; int /*<<< orphan*/  maxsz; int /*<<< orphan*/  maxaddr; int /*<<< orphan*/  bndry; int /*<<< orphan*/  align; } ;
struct proto_md {int /*<<< orphan*/  bd_tag; int /*<<< orphan*/  bd_map; struct proto_tag* tag; } ;
struct proto_ioc_busdma {uintptr_t result; } ;
struct proto_busdma {int /*<<< orphan*/  mds; int /*<<< orphan*/  bd_roottag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct proto_md*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PROTO_BUSDMA ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct proto_md*,int /*<<< orphan*/ ) ; 
 struct proto_md* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mds ; 
 int /*<<< orphan*/  peers ; 

__attribute__((used)) static int
proto_busdma_md_create(struct proto_busdma *busdma, struct proto_tag *tag,
    struct proto_ioc_busdma *ioc)
{
	struct proto_md *md;
	int error;

	md = malloc(sizeof(*md), M_PROTO_BUSDMA, M_WAITOK | M_ZERO);
	md->tag = tag;

	error = bus_dma_tag_create(busdma->bd_roottag, tag->align, tag->bndry,
	    tag->maxaddr, BUS_SPACE_MAXADDR, NULL, NULL, tag->maxsz,
	    tag->nsegs, tag->maxsegsz, 0, NULL, NULL, &md->bd_tag);
	if (error) {
		free(md, M_PROTO_BUSDMA);
		return (error);
	}
	error = bus_dmamap_create(md->bd_tag, 0, &md->bd_map);
	if (error) {
		bus_dma_tag_destroy(md->bd_tag);
		free(md, M_PROTO_BUSDMA);
		return (error);
	}

	LIST_INSERT_HEAD(&tag->mds, md, peers);
	LIST_INSERT_HEAD(&busdma->mds, md, mds);
	ioc->result = (uintptr_t)(void *)md;
	return (0);
}