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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (scalar_t__) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ verb ; 

__attribute__((used)) static int
try_read_anchor(const char* file)
{
	int empty = 1;
	char line[10240];
	char* p;
	FILE* in = fopen(file, "r");
	if(!in) {
		/* only if the file does not exist, can we fix it */
		if(errno != ENOENT) {
			if(verb) printf("%s: %s\n", file, strerror(errno));
			if(verb) printf("error: cannot access the file\n");
			exit(0);
		}
		if(verb) printf("%s does not exist\n", file);
		return 0;
	}
	while(fgets(line, (int)sizeof(line), in)) {
		line[sizeof(line)-1] = 0;
		if(strncmp(line, ";;REVOKED", 9) == 0) {
			fclose(in);
			if(verb) printf("%s : the trust point is revoked\n"
				"and the zone is considered unsigned.\n"
				"if you wish to re-enable, delete the file\n",
				file);
			return 1;
		}
		p=line;
		while(*p == ' ' || *p == '\t')
			p++;
		if(p[0]==0 || p[0]=='\n' || p[0]==';') continue;
		/* this line is a line of content */
		empty = 0;
	}
	fclose(in);
	if(empty) {
		if(verb) printf("%s is empty\n", file);
		return 0;
	}
	if(verb) printf("%s has content\n", file);
	return 2;
}