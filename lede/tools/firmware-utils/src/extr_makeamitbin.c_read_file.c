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
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 long fread (unsigned char*,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (long) ; 

unsigned char *read_file(const char *name, long *size)
{
	FILE *f;
	unsigned char *data = NULL;
	*size = 0;
	f = fopen(name, "r");
	if (f != NULL)
	{
		if (fseek(f, 0, SEEK_END) == 0)
		{
	    *size = ftell(f);
			if (*size != -1)
			{
				if (fseek(f, 0, SEEK_SET) == 0)
				{
					data = (unsigned char *)malloc(*size);
					if (data != NULL)
					{
						if (fread(data, sizeof(char), *size, f) != *size)
						{
							free(data);
							data = NULL;
						}
					}
				}
			}
		}
		fclose(f);
	}
	return data;
}