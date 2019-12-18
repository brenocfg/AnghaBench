#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  file; int /*<<< orphan*/ * pfile_in_zip_read; } ;
typedef  TYPE_1__ unz_s ;
typedef  int /*<<< orphan*/ * unzFile ;

/* Variables and functions */
 int UNZ_OK ; 
 int UNZ_PARAMERROR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose_ql (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  unzCloseCurrentFile (int /*<<< orphan*/ *) ; 
 int unz_GAME_QL ; 

extern int unzClose (unzFile file)
{
	unz_s* s;
	if (file==NULL)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;

    if (s->pfile_in_zip_read!=NULL)
        unzCloseCurrentFile(file);

	if (unz_GAME_QL == 1) {
		fclose_ql(s->file);
	} else {
		fclose(s->file);
	}
	
	free(s);
	return UNZ_OK;
}