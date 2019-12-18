#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  void uint8_t ;
struct TYPE_5__ {int ish_vsize; } ;
struct TYPE_6__ {int ish_rawdataaddr; int ish_rawdatasize; int ish_vaddr; TYPE_1__ ish_misc; } ;
typedef  TYPE_2__ image_section_header ;
struct TYPE_7__ {int /*<<< orphan*/  ioh_filealign; } ;
typedef  TYPE_3__ image_optional_header ;
typedef  int /*<<< orphan*/  image_nt_header ;
typedef  int /*<<< orphan*/  image_dos_header ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_HDRS (void*) ; 
 int /*<<< orphan*/  bcopy (void*,void*,int) ; 
 int /*<<< orphan*/  bzero (void*,scalar_t__) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 scalar_t__ pe_get_optional_header (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int pe_numsections (int /*<<< orphan*/ ) ; 
 void* realloc (void*,int) ; 

__attribute__((used)) static int
insert_padding(void **imgbase, int *imglen)
{
        image_section_header	*sect_hdr;
        image_dos_header	*dos_hdr;
        image_nt_header		*nt_hdr;
	image_optional_header	opt_hdr;
        int			i = 0, sections, curlen = 0;
	int			offaccum = 0, oldraddr, oldrlen;
	uint8_t			*newimg, *tmp;

	newimg = malloc(*imglen);

	if (newimg == NULL)
		return(ENOMEM);

	bcopy(*imgbase, newimg, *imglen);
	curlen = *imglen;

	if (pe_get_optional_header((vm_offset_t)newimg, &opt_hdr))
		return(0);

        sections = pe_numsections((vm_offset_t)newimg);

	SET_HDRS(newimg);

	for (i = 0; i < sections; i++) {
		oldraddr = sect_hdr->ish_rawdataaddr;
		oldrlen = sect_hdr->ish_rawdatasize;
		sect_hdr->ish_rawdataaddr = sect_hdr->ish_vaddr;
		offaccum += ROUND_UP(sect_hdr->ish_vaddr - oldraddr,
		    opt_hdr.ioh_filealign);
		offaccum +=
		    ROUND_UP(sect_hdr->ish_misc.ish_vsize,
			     opt_hdr.ioh_filealign) -
		    ROUND_UP(sect_hdr->ish_rawdatasize,
			     opt_hdr.ioh_filealign);
		tmp = realloc(newimg, *imglen + offaccum);
		if (tmp == NULL) {
			free(newimg);
			return(ENOMEM);
		}
		newimg = tmp;
		SET_HDRS(newimg);
		sect_hdr += i;
		bzero(newimg + sect_hdr->ish_rawdataaddr,
		    ROUND_UP(sect_hdr->ish_misc.ish_vsize,
		    opt_hdr.ioh_filealign));
		bcopy((uint8_t *)(*imgbase) + oldraddr,
		    newimg + sect_hdr->ish_rawdataaddr, oldrlen);
		sect_hdr++;
	}

	free(*imgbase);

	*imgbase = newimg;
	*imglen += offaccum;

	return(0);
}