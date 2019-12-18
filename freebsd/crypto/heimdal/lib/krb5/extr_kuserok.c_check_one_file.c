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
struct stat {int st_mode; scalar_t__ st_uid; } ;
struct passwd {scalar_t__ pw_uid; } ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_boolean ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EISDIR ; 
 int EOF ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_cloexec_file (int /*<<< orphan*/ *) ; 
 int strcspn (char*,char*) ; 

__attribute__((used)) static krb5_error_code
check_one_file(krb5_context context,
	       const char *filename,
	       struct passwd *pwd,
	       krb5_principal principal,
	       krb5_boolean *result)
{
    FILE *f;
    char buf[BUFSIZ];
    krb5_error_code ret;
    struct stat st;

    *result = FALSE;

    f = fopen (filename, "r");
    if (f == NULL)
	return errno;
    rk_cloexec_file(f);

    /* check type and mode of file */
    if (fstat(fileno(f), &st) != 0) {
	fclose (f);
	return errno;
    }
    if (S_ISDIR(st.st_mode)) {
	fclose (f);
	return EISDIR;
    }
    if (st.st_uid != pwd->pw_uid && st.st_uid != 0) {
	fclose (f);
	return EACCES;
    }
    if ((st.st_mode & (S_IWGRP | S_IWOTH)) != 0) {
	fclose (f);
	return EACCES;
    }

    while (fgets (buf, sizeof(buf), f) != NULL) {
	krb5_principal tmp;
	char *newline = buf + strcspn(buf, "\n");

	if(*newline != '\n') {
	    int c;
	    c = fgetc(f);
	    if(c != EOF) {
		while(c != EOF && c != '\n')
		    c = fgetc(f);
		/* line was too long, so ignore it */
		continue;
	    }
	}
	*newline = '\0';
	ret = krb5_parse_name (context, buf, &tmp);
	if (ret)
	    continue;
	*result = krb5_principal_compare (context, principal, tmp);
	krb5_free_principal (context, tmp);
	if (*result) {
	    fclose (f);
	    return 0;
	}
    }
    fclose (f);
    return 0;
}