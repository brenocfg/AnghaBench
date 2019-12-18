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
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hdb_db_dir (int /*<<< orphan*/ ) ; 
 char* krb5_config_get_string_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 char* slave_stats_file ; 

__attribute__((used)) static FILE *
open_stats(krb5_context context)
{
    char *statfile = NULL;
    const char *fn;
    FILE *f;

    if (slave_stats_file)
	fn = slave_stats_file;
    else {
	asprintf(&statfile,  "%s/slaves-stats", hdb_db_dir(context));
	fn = krb5_config_get_string_default(context,
					    NULL,
					    statfile,
					    "kdc",
					    "iprop-stats",
					    NULL);
    }
    f = fopen(fn, "w");
    if (statfile)
	free(statfile);

    return f;
}