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
 scalar_t__ builtin_ls (int /*<<< orphan*/ *,char*) ; 
 int data ; 
 int /*<<< orphan*/ * dataconn (char*,int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int pdata ; 
 int /*<<< orphan*/  reply (int,char*) ; 
 int /*<<< orphan*/  retrieve (char const*,char*) ; 
 int /*<<< orphan*/  set_buffer_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ use_builtin_ls ; 

void
list_file(char *file)
{
    if(use_builtin_ls) {
	FILE *dout;
	dout = dataconn(file, -1, "w");
	if (dout == NULL)
	    return;
	set_buffer_size(fileno(dout), 0);
	if(builtin_ls(dout, file) == 0)
	    reply(226, "Transfer complete.");
	else
	    reply(451, "Requested action aborted. Local error in processing.");
	fclose(dout);
	data = -1;
	pdata = -1;
    } else {
#ifdef HAVE_LS_A
	const char *cmd = "/bin/ls -lA %s";
#else
	const char *cmd = "/bin/ls -la %s";
#endif
	retrieve(cmd, file);
    }
}