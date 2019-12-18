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
struct hdrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int HDRSIZE ; 
 char* ascii1 ; 
 char* ascii2 ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 struct hdrinfo* find_hdrinfo (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int fwrite (unsigned char*,long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makehdr (unsigned char*,struct hdrinfo*,unsigned char*,long,int) ; 
 int /*<<< orphan*/  oferror (int /*<<< orphan*/ *) ; 
 unsigned char* read_file (char*,long*) ; 
 int /*<<< orphan*/  show_fwids () ; 
 int /*<<< orphan*/  showhelp () ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int main(int argc, char *argv[])
{
	unsigned char hdr[HDRSIZE];
	unsigned char *data;
	FILE *of;
	char *outfile = NULL;
	char *type;
	struct hdrinfo *info;
	long size;
	int last = 0;
	int n;
	for (n = 1; n < argc; n++)
	{
		if (strcmp(argv[n], "-1") == 0)
			ascii1 = argv[n+1];
		if (strcmp(argv[n], "-2") == 0)
			ascii2 = argv[n+1];
		if (strcmp(argv[n], "-o") == 0)
			outfile = argv[n+1];
		if (strcmp(argv[n], "-ids") == 0)
			show_fwids();
	}
	if (ascii1 == NULL || ascii2 == NULL || outfile == NULL)
		showhelp();
	of = fopen(outfile, "w");
	if (of == NULL)
		oferror(of);
	for (n = 1; n < argc; n++)
	{
		if (strncmp(argv[n], "-", 1) != 0)
		{
			type = argv[n++];
			if (n >= argc)
				showhelp();
			last = ((n + 1) >= argc);		/* dirty, options first! */
			info = find_hdrinfo(type);
			if (info == NULL)
				showhelp();
			data = read_file(argv[n], &size);
			if (data == NULL)
				showhelp();
			makehdr(hdr, info, data, size, last);
			/* showhdr(hdr); */
			if (fwrite(hdr, HDRSIZE, 1, of) != 1)
				oferror(of);
			if (fwrite(data, size, 1, of) != 1)
				oferror(of);
			free(data);
		}
		else
			n++;
	}
	if (fclose(of) != 0)
		oferror(NULL);
	return 0;
}