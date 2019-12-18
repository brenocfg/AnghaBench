#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* pakfile; char* filename; char* origname; int zipfile; int offset; int length; struct TYPE_10__* next; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ quakefile_t ;
struct TYPE_11__ {scalar_t__ ident; int dirofs; int dirlen; char* name; int filepos; int filelen; } ;
typedef  TYPE_2__ dsinpackfile_t ;
typedef  TYPE_2__ dpackheader_t ;
typedef  TYPE_2__ dpackfile_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertPath (char*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ FileFilter (char*,char*,int) ; 
 scalar_t__ IDPAKHEADER ; 
 int LittleLong (int) ; 
 int /*<<< orphan*/  QuakeFileType (char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SINPAKHEADER ; 
 int /*<<< orphan*/  Warning (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

quakefile_t *FindQuakeFilesInPak(char *pakfile, char *filter)
{
	FILE *fp;
	dpackheader_t packheader;
	dsinpackfile_t *packfiles;
	dpackfile_t *idpackfiles;
	quakefile_t *qfiles, *lastqf, *qf;
	int numpackdirs, i;

	qfiles = NULL;
	lastqf = NULL;
	//open the pak file
	fp = fopen(pakfile, "rb");
	if (!fp)
	{
		Warning("can't open pak file %s", pakfile);
		return NULL;
	} //end if
	//read pak header, check for valid pak id and seek to the dir entries
	if ((fread(&packheader, 1, sizeof(dpackheader_t), fp) != sizeof(dpackheader_t))
		|| (packheader.ident != IDPAKHEADER && packheader.ident != SINPAKHEADER)
		||	(fseek(fp, LittleLong(packheader.dirofs), SEEK_SET))
		)
	{
		fclose(fp);
		Warning("invalid pak file %s", pakfile);
		return NULL;
	} //end if
	//if it is a pak file from id software
	if (packheader.ident == IDPAKHEADER)
	{
		//number of dir entries in the pak file
		numpackdirs = LittleLong(packheader.dirlen) / sizeof(dpackfile_t);
		idpackfiles = (dpackfile_t *) malloc(numpackdirs * sizeof(dpackfile_t));
		if (!idpackfiles) Error("out of memory");
		//read the dir entry
		if (fread(idpackfiles, sizeof(dpackfile_t), numpackdirs, fp) != numpackdirs)
		{
			fclose(fp);
			free(idpackfiles);
			Warning("can't read the Quake pak file dir entries from %s", pakfile);
			return NULL;
		} //end if
		fclose(fp);
		//convert to sin pack files
		packfiles = (dsinpackfile_t *) malloc(numpackdirs * sizeof(dsinpackfile_t));
		if (!packfiles) Error("out of memory");
		for (i = 0; i < numpackdirs; i++)
		{
			strcpy(packfiles[i].name, idpackfiles[i].name);
			packfiles[i].filepos = LittleLong(idpackfiles[i].filepos);
			packfiles[i].filelen = LittleLong(idpackfiles[i].filelen);
		} //end for
		free(idpackfiles);
	} //end if
	else //its a Sin pack file
	{
		//number of dir entries in the pak file
		numpackdirs = LittleLong(packheader.dirlen) / sizeof(dsinpackfile_t);
		packfiles = (dsinpackfile_t *) malloc(numpackdirs * sizeof(dsinpackfile_t));
		if (!packfiles) Error("out of memory");
		//read the dir entry
		if (fread(packfiles, sizeof(dsinpackfile_t), numpackdirs, fp) != numpackdirs)
		{
			fclose(fp);
			free(packfiles);
			Warning("can't read the Sin pak file dir entries from %s", pakfile);
			return NULL;
		} //end if
		fclose(fp);
		for (i = 0; i < numpackdirs; i++)
		{
			packfiles[i].filepos = LittleLong(packfiles[i].filepos);
			packfiles[i].filelen = LittleLong(packfiles[i].filelen);
		} //end for
	} //end else
	//
	for (i = 0; i < numpackdirs; i++)
	{
		ConvertPath(packfiles[i].name);
		if (FileFilter(filter, packfiles[i].name, false))
		{
			qf = malloc(sizeof(quakefile_t));
			if (!qf) Error("out of memory");
			memset(qf, 0, sizeof(quakefile_t));
			strcpy(qf->pakfile, pakfile);
			strcpy(qf->filename, pakfile);
			strcpy(qf->origname, packfiles[i].name);
			qf->zipfile = false;
			qf->offset = packfiles[i].filepos;
			qf->length = packfiles[i].filelen;
			qf->type = QuakeFileType(packfiles[i].name);
			//add the file ot the list
			qf->next = NULL;
			if (lastqf) lastqf->next = qf;
			else qfiles = qf;
			lastqf = qf;
		} //end if
	} //end for
	free(packfiles);
	return qfiles;
}