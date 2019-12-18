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
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtree_global ; 
 int read_mtree_keywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int read_word (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  skip_to (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
read_mtree_command(FILE *fp)
{
	char cmd[10];
	int error;

	error = read_word(fp, cmd, sizeof(cmd));
	if (error)
		goto out;

	error = read_mtree_keywords(fp, &mtree_global);

 out:
	skip_to(fp, "\n");
	(void)getc(fp);
	return (error);
}