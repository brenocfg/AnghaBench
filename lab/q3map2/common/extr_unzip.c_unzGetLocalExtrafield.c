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
struct TYPE_3__ {TYPE_2__* pfile_in_zip_read; } ;
typedef  TYPE_1__ unz_s ;
typedef  int /*<<< orphan*/ * unzFile ;
typedef  unsigned int uLong ;
typedef  scalar_t__ uInt ;
struct TYPE_4__ {unsigned int size_local_extrafield; unsigned int pos_local_extrafield; unsigned int offset_local_extrafield; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ file_in_zip_read_info_s ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int UNZ_ERRNO ; 
 int UNZ_PARAMERROR ; 
 int fread (void*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

extern int unzGetLocalExtrafield (unzFile file,void *buf,unsigned len)
{
	unz_s* s;
	file_in_zip_read_info_s* pfile_in_zip_read_info;
	uInt read_now;
	uLong size_to_read;

	if (file==NULL)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
    pfile_in_zip_read_info=s->pfile_in_zip_read;

	if (pfile_in_zip_read_info==NULL)
		return UNZ_PARAMERROR;

	size_to_read = (pfile_in_zip_read_info->size_local_extrafield - 
				pfile_in_zip_read_info->pos_local_extrafield);

	if (buf==NULL)
		return (int)size_to_read;
	
	if (len>size_to_read)
		read_now = (uInt)size_to_read;
	else
		read_now = (uInt)len ;

	if (read_now==0)
		return 0;
	
	if (fseek(pfile_in_zip_read_info->file,
              pfile_in_zip_read_info->offset_local_extrafield + 
			  pfile_in_zip_read_info->pos_local_extrafield,SEEK_SET)!=0)
		return UNZ_ERRNO;

	if (fread(buf,(uInt)size_to_read,1,pfile_in_zip_read_info->file)!=1)
		return UNZ_ERRNO;

	return (int)read_now;
}