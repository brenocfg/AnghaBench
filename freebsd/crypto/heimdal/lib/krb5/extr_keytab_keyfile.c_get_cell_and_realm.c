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
struct akf_data {int /*<<< orphan*/ * cell; int /*<<< orphan*/ * realm; } ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_SERVERMAGICKRBCONF ; 
 int /*<<< orphan*/  AFS_SERVERTHISCELL ; 
 int BUFSIZ ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 size_t strcspn (char*,char*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 char toupper (unsigned char) ; 

__attribute__((used)) static int
get_cell_and_realm (krb5_context context, struct akf_data *d)
{
    FILE *f;
    char buf[BUFSIZ], *cp;
    int ret;

    f = fopen (AFS_SERVERTHISCELL, "r");
    if (f == NULL) {
	ret = errno;
	krb5_set_error_message (context, ret,
				N_("Open ThisCell %s: %s", ""),
				AFS_SERVERTHISCELL,
				strerror(ret));
	return ret;
    }
    if (fgets (buf, sizeof(buf), f) == NULL) {
	fclose (f);
	krb5_set_error_message (context, EINVAL,
				N_("No cell in ThisCell file %s", ""),
				AFS_SERVERTHISCELL);
	return EINVAL;
    }
    buf[strcspn(buf, "\n")] = '\0';
    fclose(f);

    d->cell = strdup (buf);
    if (d->cell == NULL) {
	krb5_set_error_message(context, ENOMEM,
			       N_("malloc: out of memory", ""));
	return ENOMEM;
    }

    f = fopen (AFS_SERVERMAGICKRBCONF, "r");
    if (f != NULL) {
	if (fgets (buf, sizeof(buf), f) == NULL) {
	    free (d->cell);
	    d->cell = NULL;
	    fclose (f);
	    krb5_set_error_message (context, EINVAL,
				    N_("No realm in ThisCell file %s", ""),
				    AFS_SERVERMAGICKRBCONF);
	    return EINVAL;
	}
	buf[strcspn(buf, "\n")] = '\0';
	fclose(f);
    }
    /* uppercase */
    for (cp = buf; *cp != '\0'; cp++)
	*cp = toupper((unsigned char)*cp);

    d->realm = strdup (buf);
    if (d->realm == NULL) {
	free (d->cell);
	d->cell = NULL;
	krb5_set_error_message(context, ENOMEM,
			       N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    return 0;
}