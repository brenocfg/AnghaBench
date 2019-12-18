#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unz_s ;
struct TYPE_9__ {int number_entry; } ;
typedef  TYPE_1__ unz_global_info ;
struct TYPE_10__ {int /*<<< orphan*/  uncompressed_size; } ;
typedef  TYPE_2__ unz_file_info ;
typedef  scalar_t__ unzFile ;
struct TYPE_11__ {int zipfile; struct TYPE_11__* next; int /*<<< orphan*/  type; int /*<<< orphan*/  length; scalar_t__ offset; int /*<<< orphan*/  zipinfo; int /*<<< orphan*/  origname; int /*<<< orphan*/  filename; int /*<<< orphan*/  pakfile; } ;
typedef  TYPE_3__ quakefile_t ;
typedef  int /*<<< orphan*/  filename_inzip ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertPath (char*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ FileFilter (char*,char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  QuakeFileType (char*) ; 
 int UNZ_OK ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unzClose (scalar_t__) ; 
 int unzGetCurrentFileInfo (scalar_t__,TYPE_2__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int unzGetGlobalInfo (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  unzGoToFirstFile (scalar_t__) ; 
 int /*<<< orphan*/  unzGoToNextFile (scalar_t__) ; 
 scalar_t__ unzOpen (char*) ; 

quakefile_t *FindQuakeFilesInZip(char *zipfile, char *filter)
{
	unzFile			uf;
	int				err;
	unz_global_info gi;
	char			filename_inzip[MAX_PATH];
	unz_file_info	file_info;
	int				i;
	quakefile_t		*qfiles, *lastqf, *qf;

	uf = unzOpen(zipfile);
	err = unzGetGlobalInfo(uf, &gi);

	if (err != UNZ_OK) return NULL;

	unzGoToFirstFile(uf);

	qfiles = NULL;
	lastqf = NULL;
	for (i = 0; i < gi.number_entry; i++)
	{
		err = unzGetCurrentFileInfo(uf, &file_info, filename_inzip, sizeof(filename_inzip), NULL,0,NULL,0);
		if (err != UNZ_OK) break;

		ConvertPath(filename_inzip);
		if (FileFilter(filter, filename_inzip, false))
		{
			qf = malloc(sizeof(quakefile_t));
			if (!qf) Error("out of memory");
			memset(qf, 0, sizeof(quakefile_t));
			strcpy(qf->pakfile, zipfile);
			strcpy(qf->filename, zipfile);
			strcpy(qf->origname, filename_inzip);
			qf->zipfile = true;
			//memcpy( &buildBuffer[i].zipfileinfo, (unz_s*)uf, sizeof(unz_s));
			memcpy(&qf->zipinfo, (unz_s*)uf, sizeof(unz_s));
			qf->offset = 0;
			qf->length = file_info.uncompressed_size;
			qf->type = QuakeFileType(filename_inzip);
			//add the file ot the list
			qf->next = NULL;
			if (lastqf) lastqf->next = qf;
			else qfiles = qf;
			lastqf = qf;
		} //end if
		unzGoToNextFile(uf);
	} //end for

	unzClose(uf);

	return qfiles;
}