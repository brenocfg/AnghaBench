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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (char*,char*) ; 
 int verb ; 

__attribute__((used)) static int
read_if_pending_keys(const char* file)
{
	FILE* in = fopen(file, "r");
	char line[8192];
	if(!in) {
		if(verb>=2) printf("%s: %s\n", file, strerror(errno));
		return 0;
	}
	while(fgets(line, (int)sizeof(line), in)) {
		if(line[0]==';') continue;
		if(strstr(line, "[ ADDPEND ]")) {
			fclose(in);
			if(verb) printf("RFC5011-state has ADDPEND keys\n");
			return 1;
		}
	}
	fclose(in);
	return 0;
}