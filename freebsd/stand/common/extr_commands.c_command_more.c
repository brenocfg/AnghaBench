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

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 int page_file (char*) ; 
 int /*<<< orphan*/  pager_close () ; 
 int /*<<< orphan*/  pager_open () ; 
 int pager_output (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int
command_more(int argc, char *argv[])
{
	int	i;
	int	res;
	char	line[80];

	res = 0;
	pager_open();
	for (i = 1; (i < argc) && (res == 0); i++) {
		snprintf(line, sizeof(line), "*** FILE %s BEGIN ***\n",
		    argv[i]);
		if (pager_output(line))
			break;
		res = page_file(argv[i]);
		if (!res) {
			snprintf(line, sizeof(line), "*** FILE %s END ***\n",
			    argv[i]);
			res = pager_output(line);
		}
	}
	pager_close();

	if (res == 0)
		return (CMD_OK);
	else
		return (CMD_ERROR);
}