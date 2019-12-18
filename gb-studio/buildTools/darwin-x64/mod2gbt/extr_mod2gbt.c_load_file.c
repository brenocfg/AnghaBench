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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (void*,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ftell (int /*<<< orphan*/ *) ; 
 void* malloc (unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

void * load_file(const char * filename)
{
	FILE * datafile = fopen(filename, "rb");
	unsigned int size;
	void * buffer = NULL;

	if(datafile == NULL)
	{
        printf("\n\nERROR: %s couldn't be opened!\n\n",filename);
        return NULL;
    }

    fseek (datafile , 0 , SEEK_END);
	size = ftell (datafile);
	if(size == 0)
	{
        printf("\n\nERROR: Size of %s is 0!\n\n",filename);
        fclose(datafile);
        return NULL;
    }
	rewind (datafile);
	buffer = malloc(size);
	if(buffer == NULL)
	{
        printf("\n\nERROR: Not enought memory to load %s!\n\n",filename);
        fclose(datafile);
        return NULL;
    }
	if(fread(buffer,size,1,datafile) != 1)
	{
        printf("\n\nERROR: Error while reading.\n\n");
        fclose(datafile);
		free(buffer);
        return NULL;
    }

	fclose(datafile);

	return buffer;
}