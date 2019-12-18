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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  lreply (int,char*,char*) ; 
 size_t strcspn (char*,char*) ; 

__attribute__((used)) static int
show_file(const char *file, int code)
{
    FILE *f;
    char buf[128];

    f = fopen(file, "r");
    if(f == NULL)
	return -1;
    while(fgets(buf, sizeof(buf), f)){
	buf[strcspn(buf, "\r\n")] = '\0';
	lreply(code, "%s", buf);
    }
    fclose(f);
    return 0;
}