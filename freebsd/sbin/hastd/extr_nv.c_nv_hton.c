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
struct nvhdr {int dummy; } ;
struct nv {scalar_t__ nv_error; struct ebuf* nv_ebuf; } ;
struct ebuf {int dummy; } ;

/* Variables and functions */
 size_t NVH_SIZE (struct nvhdr*) ; 
 int /*<<< orphan*/  NV_CHECK (struct nv*) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 unsigned char* ebuf_data (struct ebuf*,size_t*) ; 
 int /*<<< orphan*/  nv_swap (struct nvhdr*,int) ; 

struct ebuf *
nv_hton(struct nv *nv)
{
	struct nvhdr *nvh;
	unsigned char *ptr;
	size_t size;

	NV_CHECK(nv);
	PJDLOG_ASSERT(nv->nv_error == 0);

	ptr = ebuf_data(nv->nv_ebuf, &size);
	while (size > 0) {
		/*
		 * Minimum size at this point is size of nvhdr structure,
		 * one character long name plus terminating '\0'.
		 */
		PJDLOG_ASSERT(size >= sizeof(*nvh) + 2);
		nvh = (struct nvhdr *)ptr;
		PJDLOG_ASSERT(NVH_SIZE(nvh) <= size);
		nv_swap(nvh, false);
		ptr += NVH_SIZE(nvh);
		size -= NVH_SIZE(nvh);
	}

	return (nv->nv_ebuf);
}