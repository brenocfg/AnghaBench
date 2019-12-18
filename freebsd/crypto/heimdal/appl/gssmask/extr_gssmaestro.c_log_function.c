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
struct client {int /*<<< orphan*/  logsock; } ;
typedef  int int32_t ;

/* Variables and functions */
#define  eLogFailure 130 
#define  eLogInfo 129 
#define  eLogSetMoniker 128 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,unsigned long,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ krb5_ret_int32 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  krb5_ret_string (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logfile ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned long,char*) ; 

__attribute__((used)) static int
log_function(void *ptr)
{
    struct client *c = ptr;
    int32_t cmd, line;
    char *file, *string;

    while (1) {
        if (krb5_ret_int32(c->logsock, &cmd))
	    goto out;

	switch (cmd) {
	case eLogSetMoniker:
	    if (krb5_ret_string(c->logsock, &file))
		goto out;
	    free(file);
	    break;
	case eLogInfo:
	case eLogFailure:
	    if (krb5_ret_string(c->logsock, &file))
		goto out;
	    if (krb5_ret_int32(c->logsock, &line))
		goto out;
	    if (krb5_ret_string(c->logsock, &string))
		goto out;
	    printf("%s:%lu: %s\n",
		   file, (unsigned long)line, string);
	    fprintf(logfile, "%s:%lu: %s\n",
		    file, (unsigned long)line, string);
	    fflush(logfile);
	    free(file);
	    free(string);
	    if (krb5_store_int32(c->logsock, 0))
		goto out;
	    break;
	default:
	    errx(1, "client send bad log command: %d", (int)cmd);
	}
    }
out:

    return 0;
}