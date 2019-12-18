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
struct thread {int dummy; } ;
struct proto_tag {int dummy; } ;
struct proto_softc {int /*<<< orphan*/  sc_dev; } ;
struct proto_md {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tag; } ;
struct TYPE_4__ {TYPE_1__ md; } ;
struct proto_ioc_busdma {int request; int /*<<< orphan*/  key; TYPE_2__ u; } ;
struct proto_busdma {int /*<<< orphan*/  sxlck; int /*<<< orphan*/  bd_roottag; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PROTO_IOC_BUSDMA_MD_CREATE 137 
#define  PROTO_IOC_BUSDMA_MD_DESTROY 136 
#define  PROTO_IOC_BUSDMA_MD_LOAD 135 
#define  PROTO_IOC_BUSDMA_MD_UNLOAD 134 
#define  PROTO_IOC_BUSDMA_MEM_ALLOC 133 
#define  PROTO_IOC_BUSDMA_MEM_FREE 132 
#define  PROTO_IOC_BUSDMA_SYNC 131 
#define  PROTO_IOC_BUSDMA_TAG_CREATE 130 
#define  PROTO_IOC_BUSDMA_TAG_DERIVE 129 
#define  PROTO_IOC_BUSDMA_TAG_DESTROY 128 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int proto_busdma_md_create (struct proto_busdma*,struct proto_tag*,struct proto_ioc_busdma*) ; 
 int proto_busdma_md_destroy (struct proto_busdma*,struct proto_md*) ; 
 int proto_busdma_md_load (struct proto_busdma*,struct proto_md*,struct proto_ioc_busdma*,struct thread*) ; 
 struct proto_md* proto_busdma_md_lookup (struct proto_busdma*,int /*<<< orphan*/ ) ; 
 int proto_busdma_md_unload (struct proto_busdma*,struct proto_md*) ; 
 int proto_busdma_mem_alloc (struct proto_busdma*,struct proto_tag*,struct proto_ioc_busdma*) ; 
 int proto_busdma_mem_free (struct proto_busdma*,struct proto_md*) ; 
 int proto_busdma_sync (struct proto_busdma*,struct proto_md*,struct proto_ioc_busdma*) ; 
 int proto_busdma_tag_create (struct proto_busdma*,struct proto_tag*,struct proto_ioc_busdma*) ; 
 int proto_busdma_tag_destroy (struct proto_busdma*,struct proto_tag*) ; 
 struct proto_tag* proto_busdma_tag_lookup (struct proto_busdma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
proto_busdma_ioctl(struct proto_softc *sc, struct proto_busdma *busdma,
    struct proto_ioc_busdma *ioc, struct thread *td)
{
	struct proto_tag *tag;
	struct proto_md *md;
	int error;

	sx_xlock(&busdma->sxlck);

	error = 0;
	switch (ioc->request) {
	case PROTO_IOC_BUSDMA_TAG_CREATE:
		busdma->bd_roottag = bus_get_dma_tag(sc->sc_dev);
		error = proto_busdma_tag_create(busdma, NULL, ioc);
		break;
	case PROTO_IOC_BUSDMA_TAG_DERIVE:
		tag = proto_busdma_tag_lookup(busdma, ioc->key);
		if (tag == NULL) {
			error = EINVAL;
			break;
		}
		error = proto_busdma_tag_create(busdma, tag, ioc);
		break;
	case PROTO_IOC_BUSDMA_TAG_DESTROY:
		tag = proto_busdma_tag_lookup(busdma, ioc->key);
		if (tag == NULL) {
			error = EINVAL;
			break;
		}
		error = proto_busdma_tag_destroy(busdma, tag);
		break;
	case PROTO_IOC_BUSDMA_MEM_ALLOC:
		tag = proto_busdma_tag_lookup(busdma, ioc->u.md.tag);
		if (tag == NULL) {
			error = EINVAL;
			break;
		}
		error = proto_busdma_mem_alloc(busdma, tag, ioc);
		break;
	case PROTO_IOC_BUSDMA_MEM_FREE:
		md = proto_busdma_md_lookup(busdma, ioc->key);
		if (md == NULL) {
			error = EINVAL;
			break;
		}
		error = proto_busdma_mem_free(busdma, md);
		break;
	case PROTO_IOC_BUSDMA_MD_CREATE:
		tag = proto_busdma_tag_lookup(busdma, ioc->u.md.tag);
		if (tag == NULL) {
			error = EINVAL;
			break;
		}
		error = proto_busdma_md_create(busdma, tag, ioc);
		break;
	case PROTO_IOC_BUSDMA_MD_DESTROY:
		md = proto_busdma_md_lookup(busdma, ioc->key);
		if (md == NULL) {
			error = EINVAL;
			break;
		}
		error = proto_busdma_md_destroy(busdma, md);
		break;
	case PROTO_IOC_BUSDMA_MD_LOAD:
		md = proto_busdma_md_lookup(busdma, ioc->key);
		if (md == NULL) {
			error = EINVAL;
			break;
		}
		error = proto_busdma_md_load(busdma, md, ioc, td);
		break;
	case PROTO_IOC_BUSDMA_MD_UNLOAD:
		md = proto_busdma_md_lookup(busdma, ioc->key);
		if (md == NULL) {
			error = EINVAL;
			break;
		}
		error = proto_busdma_md_unload(busdma, md);
		break;
	case PROTO_IOC_BUSDMA_SYNC:
		md = proto_busdma_md_lookup(busdma, ioc->key);
		if (md == NULL) {
			error = EINVAL;
			break;
		}
		error = proto_busdma_sync(busdma, md, ioc);
		break;
	default:
		error = EINVAL;
		break;
	}

	sx_xunlock(&busdma->sxlck);

	return (error);
}