#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* nvp_name; int nvp_data; int /*<<< orphan*/  nvp_magic; } ;
typedef  TYPE_1__ nvpair_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVPAIR_MAGIC ; 
 scalar_t__ NV_NAME_MAX ; 
 TYPE_1__* nv_calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  nv_free (TYPE_1__*) ; 
 TYPE_1__* nv_realloc (TYPE_1__*,scalar_t__) ; 
 unsigned char* nvpair_unpack_header (int,TYPE_1__*,unsigned char const*,size_t*) ; 
 scalar_t__ strlen (char*) ; 

const unsigned char *
nvpair_unpack(bool isbe, const unsigned char *ptr, size_t *leftp,
    nvpair_t **nvpp)
{
	nvpair_t *nvp, *tmp;

	nvp = nv_calloc(1, sizeof(*nvp) + NV_NAME_MAX);
	if (nvp == NULL)
		return (NULL);
	nvp->nvp_name = (char *)(nvp + 1);

	ptr = nvpair_unpack_header(isbe, nvp, ptr, leftp);
	if (ptr == NULL)
		goto fail;
	tmp = nv_realloc(nvp, sizeof(*nvp) + strlen(nvp->nvp_name) + 1);
	if (tmp == NULL)
		goto fail;
	nvp = tmp;

	/* Update nvp_name after realloc(). */
	nvp->nvp_name = (char *)(nvp + 1);
	nvp->nvp_data = 0x00;
	nvp->nvp_magic = NVPAIR_MAGIC;
	*nvpp = nvp;
	return (ptr);
fail:
	nv_free(nvp);
	return (NULL);
}