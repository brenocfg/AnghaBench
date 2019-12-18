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
typedef  int /*<<< orphan*/  va_list ;
struct nvhdr {int nvh_type; int /*<<< orphan*/  nvh_name; } ;
struct nv {scalar_t__ nv_error; int /*<<< orphan*/  nv_ebuf; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 void* EINVAL ; 
 void* ENOENT ; 
 void* ENOMEM ; 
 size_t NVH_SIZE (struct nvhdr*) ; 
 int /*<<< orphan*/  NV_CHECK (struct nv*) ; 
 int NV_TYPE_MASK ; 
 int NV_TYPE_NONE ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 unsigned char* ebuf_data (int /*<<< orphan*/ ,size_t*) ; 
 void* errno ; 
 int /*<<< orphan*/  nv_swap (struct nvhdr*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 size_t vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nvhdr *
nv_find(struct nv *nv, int type, const char *namefmt, va_list nameap)
{
	char name[255];
	struct nvhdr *nvh;
	unsigned char *ptr;
	size_t size, namesize;

	if (nv == NULL) {
		errno = ENOMEM;
		return (NULL);
	}

	NV_CHECK(nv);

	namesize = vsnprintf(name, sizeof(name), namefmt, nameap);
	PJDLOG_ASSERT(namesize > 0 && namesize < sizeof(name));
	namesize++;

	ptr = ebuf_data(nv->nv_ebuf, &size);
	while (size > 0) {
		PJDLOG_ASSERT(size >= sizeof(*nvh) + 2);
		nvh = (struct nvhdr *)ptr;
		PJDLOG_ASSERT(size >= NVH_SIZE(nvh));
		nv_swap(nvh, true);
		if (strcmp(nvh->nvh_name, name) == 0) {
			if (type != NV_TYPE_NONE &&
			    (nvh->nvh_type & NV_TYPE_MASK) != type) {
				errno = EINVAL;
				if (nv->nv_error == 0)
					nv->nv_error = EINVAL;
				return (NULL);
			}
			return (nvh);
		}
		ptr += NVH_SIZE(nvh);
		size -= NVH_SIZE(nvh);
	}
	errno = ENOENT;
	if (nv->nv_error == 0)
		nv->nv_error = ENOENT;
	return (NULL);
}