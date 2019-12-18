#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ size_file_comment; scalar_t__ size_file_extra; scalar_t__ size_filename; } ;
struct TYPE_4__ {scalar_t__ number_entry; } ;
struct TYPE_5__ {int current_file_ok; scalar_t__ num_file; int /*<<< orphan*/  cur_file_info_internal; TYPE_3__ cur_file_info; int /*<<< orphan*/  pos_in_central_dir; TYPE_1__ gi; } ;
typedef  TYPE_2__ unz_s ;
typedef  int /*<<< orphan*/ * unzFile ;

/* Variables and functions */
 scalar_t__ SIZECENTRALDIRITEM ; 
 int UNZ_END_OF_LIST_OF_FILE ; 
 int UNZ_OK ; 
 int UNZ_PARAMERROR ; 
 int unzlocal_GetCurrentFileInfoInternal (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

extern int unzGoToNextFile (unzFile file)
{
	unz_s* s;	
	int err;

	if (file==NULL)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
	if (!s->current_file_ok)
		return UNZ_END_OF_LIST_OF_FILE;
	if (s->num_file+1==s->gi.number_entry)
		return UNZ_END_OF_LIST_OF_FILE;

	s->pos_in_central_dir += SIZECENTRALDIRITEM + s->cur_file_info.size_filename +
			s->cur_file_info.size_file_extra + s->cur_file_info.size_file_comment ;
	s->num_file++;
	err = unzlocal_GetCurrentFileInfoInternal(file,&s->cur_file_info,
											   &s->cur_file_info_internal,
											   NULL,0,NULL,0,NULL,0);
	s->current_file_ok = (err == UNZ_OK);
	return err;
}