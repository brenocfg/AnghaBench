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
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static char *readfile(char *filename, int *size)
{
	FILE		*fp;
	char		*buffer;
	struct stat	info;

	if (stat(filename,&info)!=0)
		return NULL;

	if ((fp=fopen(filename,"r"))==NULL)
		return NULL;

	buffer=NULL;
	for (;;)
	{
		if ((buffer=(char *)malloc(info.st_size+1))==NULL)
			break;

		if (fread(buffer,1,info.st_size,fp)!=info.st_size)
		{
			free(buffer);
			buffer=NULL;
			break;
		}

		buffer[info.st_size]='\0';
		if(size) *size = info.st_size;

		break;
	}

	(void)fclose(fp);

	return buffer;
}