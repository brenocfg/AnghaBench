#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int app_error_fatal; } ;
struct TYPE_4__ {TYPE_1__ flags; int /*<<< orphan*/ * logfile; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CK_USER_TYPE ;
typedef  int /*<<< orphan*/  CK_RV ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_GENERAL_ERROR ; 
 int /*<<< orphan*/  CKR_OK ; 
 int /*<<< orphan*/  add_certificate (char*,char const*,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 void* fopen (char const*,char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  rk_cloexec_file (int /*<<< orphan*/ *) ; 
 TYPE_2__ soft_token ; 
 int /*<<< orphan*/  st_logf (char*,...) ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strcspn (char*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static CK_RV
read_conf_file(const char *fn, CK_USER_TYPE userType, const char *pin)
{
    char buf[1024], *type, *s, *p;
    FILE *f;
    CK_RV ret = CKR_OK;
    CK_RV failed = CKR_OK;

    if (fn == NULL) {
        st_logf("Can't open configuration file.  No file specified\n");
        return CKR_GENERAL_ERROR;
    }

    f = fopen(fn, "r");
    if (f == NULL) {
	st_logf("can't open configuration file %s\n", fn);
	return CKR_GENERAL_ERROR;
    }
    rk_cloexec_file(f);

    while(fgets(buf, sizeof(buf), f) != NULL) {
	buf[strcspn(buf, "\n")] = '\0';

	st_logf("line: %s\n", buf);

	p = buf;
	while (isspace((unsigned char)*p))
	    p++;
	if (*p == '#')
	    continue;
	while (isspace((unsigned char)*p))
	    p++;

	s = NULL;
	type = strtok_r(p, "\t", &s);
	if (type == NULL)
	    continue;

	if (strcasecmp("certificate", type) == 0) {
	    char *cert, *id, *label;

	    id = strtok_r(NULL, "\t", &s);
	    if (id == NULL) {
		st_logf("no id\n");
		continue;
	    }
	    st_logf("id: %s\n", id);
	    label = strtok_r(NULL, "\t", &s);
	    if (label == NULL) {
		st_logf("no label\n");
		continue;
	    }
	    cert = strtok_r(NULL, "\t", &s);
	    if (cert == NULL) {
		st_logf("no certfiicate store\n");
		continue;
	    }

	    st_logf("adding: %s: %s in file %s\n", id, label, cert);

	    ret = add_certificate(cert, pin, id, label);
	    if (ret)
		failed = ret;
	} else if (strcasecmp("debug", type) == 0) {
	    char *name;

	    name = strtok_r(NULL, "\t", &s);
	    if (name == NULL) {
		st_logf("no filename\n");
		continue;
	    }

	    if (soft_token.logfile)
		fclose(soft_token.logfile);

	    if (strcasecmp(name, "stdout") == 0)
		soft_token.logfile = stdout;
	    else {
		soft_token.logfile = fopen(name, "a");
		if (soft_token.logfile)
		    rk_cloexec_file(soft_token.logfile);
	    }
	    if (soft_token.logfile == NULL)
		st_logf("failed to open file: %s\n", name);

	} else if (strcasecmp("app-fatal", type) == 0) {
	    char *name;

	    name = strtok_r(NULL, "\t", &s);
	    if (name == NULL) {
		st_logf("argument to app-fatal\n");
		continue;
	    }

	    if (strcmp(name, "true") == 0 || strcmp(name, "on") == 0)
		soft_token.flags.app_error_fatal = 1;
	    else if (strcmp(name, "false") == 0 || strcmp(name, "off") == 0)
		soft_token.flags.app_error_fatal = 0;
	    else
		st_logf("unknown app-fatal: %s\n", name);

	} else {
	    st_logf("unknown type: %s\n", type);
	}
    }

    fclose(f);

    return failed;
}