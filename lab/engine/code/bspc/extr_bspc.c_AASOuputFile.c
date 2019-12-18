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
struct TYPE_3__ {char* filename; int /*<<< orphan*/  origname; } ;
typedef  TYPE_1__ quakefile_t ;

/* Variables and functions */
 int /*<<< orphan*/  AppendPathSeperator (char*,int) ; 
 int /*<<< orphan*/  CreatePath (char*) ; 
 int /*<<< orphan*/  ExtractFileBase (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ExtractFileExtension (char*,char*) ; 
 int MAX_PATH ; 
 scalar_t__ access (char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  stricmp (char*,char*) ; 
 int strlen (char*) ; 

void AASOuputFile(quakefile_t *qf, char *outputpath, char *filename)
{
	char ext[MAX_PATH];

	//
	if (strlen(outputpath))
	{
		strcpy(filename, outputpath);
		//append the bsp file base
		AppendPathSeperator(filename, MAX_PATH);
		ExtractFileBase(qf->origname, &filename[strlen(filename)]);
		//append .aas
		strcat(filename, ".aas");
		return;
	} //end if
	//
	ExtractFileExtension(qf->filename, ext);
	if (!stricmp(ext, "pk3") || !stricmp(ext, "pak") || !stricmp(ext, "sin"))
	{
		strcpy(filename, qf->filename);
		while(strlen(filename) &&
				filename[strlen(filename)-1] != '\\' &&
				filename[strlen(filename)-1] != '/')
		{
			filename[strlen(filename)-1] = '\0';
		} //end while
		strcat(filename, "maps");
		if (access(filename, 0x04)) CreatePath(filename);
		//append the bsp file base
		AppendPathSeperator(filename, MAX_PATH);
		ExtractFileBase(qf->origname, &filename[strlen(filename)]);
		//append .aas
		strcat(filename, ".aas");
	} //end if
	else
	{
		strcpy(filename, qf->filename);
		while(strlen(filename) &&
				filename[strlen(filename)-1] != '.')
		{
			filename[strlen(filename)-1] = '\0';
		} //end while
		strcat(filename, "aas");
	} //end else
}