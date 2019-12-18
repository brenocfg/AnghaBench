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
struct pfr_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUF_SIZE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pfctl_fopen (char*,char*) ; 
 int pfr_next_token (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
pfr_buf_load(struct pfr_buffer *b, char *file, int nonetwork,
    int (*append_addr)(struct pfr_buffer *, char *, int))
{
	FILE	*fp;
	char	 buf[BUF_SIZE];
	int	 rv;

	if (file == NULL)
		return (0);
	if (!strcmp(file, "-"))
		fp = stdin;
	else {
		fp = pfctl_fopen(file, "r");
		if (fp == NULL)
			return (-1);
	}
	while ((rv = pfr_next_token(buf, fp)) == 1)
		if (append_addr(b, buf, nonetwork)) {
			rv = -1;
			break;
		}
	if (fp != stdin)
		fclose(fp);
	return (rv);
}