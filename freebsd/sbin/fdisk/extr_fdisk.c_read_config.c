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
 scalar_t__ current_line_number ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int process_line (char*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
read_config(char *config_file)
{
    FILE	*fp = NULL;
    int		status = 1;
    char	buf[1010];

	while (1) {
		if (strcmp(config_file, "-") != 0) {
	    /*
	     * We're not reading from stdin
	     */
			if ((fp = fopen(config_file, "r")) == NULL) {
		status = 0;
		break;
	    }
		} else {
	    fp = stdin;
	}
	current_line_number = 0;
		while (!feof(fp)) {
	    if (fgets(buf, sizeof(buf), fp) == NULL)
		break;
	    ++current_line_number;
	    status = process_line(buf);
	    if (status == 0)
		break;
	    }
	break;
    }
	if (fp) {
	/*
	 * It doesn't matter if we're reading from stdin, as we've reached EOF
	 */
	fclose(fp);
    }
    return (status);
}