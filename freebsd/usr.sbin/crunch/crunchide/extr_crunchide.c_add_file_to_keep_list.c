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
typedef  int /*<<< orphan*/  symbol ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_keep_list (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 

void
add_file_to_keep_list(char *filename)
{
    FILE *keepf;
    char symbol[1024];
    int len;

    if((keepf = fopen(filename, "r")) == NULL) {
	perror(filename);
	usage();
    }

    while(fgets(symbol, sizeof(symbol), keepf)) {
	len = strlen(symbol);
	if(len && symbol[len-1] == '\n')
	    symbol[len-1] = '\0';

	add_to_keep_list(symbol);
    }
    fclose(keepf);
}