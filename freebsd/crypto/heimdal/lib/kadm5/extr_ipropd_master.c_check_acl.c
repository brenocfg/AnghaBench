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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hdb_db_dir (int /*<<< orphan*/ ) ; 
 char* krb5_config_get_string_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 size_t strcspn (char*,char*) ; 

__attribute__((used)) static int
check_acl (krb5_context context, const char *name)
{
    const char *fn;
    FILE *fp;
    char buf[256];
    int ret = 1;
    char *slavefile = NULL;

    if (asprintf(&slavefile, "%s/slaves", hdb_db_dir(context)) == -1
	|| slavefile == NULL)
	errx(1, "out of memory");

    fn = krb5_config_get_string_default(context,
					NULL,
					slavefile,
					"kdc",
					"iprop-acl",
					NULL);

    fp = fopen (fn, "r");
    free(slavefile);
    if (fp == NULL)
	return 1;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
	buf[strcspn(buf, "\r\n")] = '\0';
	if (strcmp (buf, name) == 0) {
	    ret = 0;
	    break;
	}
    }
    fclose (fp);
    return ret;
}