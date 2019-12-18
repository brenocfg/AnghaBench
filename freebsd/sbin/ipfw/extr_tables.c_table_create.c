#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xi ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  tbuf ;
struct TYPE_5__ {scalar_t__ limit; int type; scalar_t__ tflags; scalar_t__ vmask; char* algoname; scalar_t__ flags; } ;
typedef  TYPE_1__ ipfw_xtable_info ;
typedef  int /*<<< orphan*/  ipfw_obj_header ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 scalar_t__ IPFW_TABLE_ADDR ; 
 scalar_t__ IPFW_TGFLAGS_LOCKED ; 
 scalar_t__ IPFW_VTYPE_LEGACY ; 
 int /*<<< orphan*/  NEED1 (char*) ; 
#define  TOK_ALGO 134 
#define  TOK_LIMIT 133 
#define  TOK_LOCK 132 
#define  TOK_MISSING 131 
#define  TOK_ORFLUSH 130 
#define  TOK_TYPE 129 
#define  TOK_VALTYPE 128 
 int /*<<< orphan*/  concat_tokens (char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int fill_flags (int /*<<< orphan*/ ,char*,char**,scalar_t__*,scalar_t__*) ; 
 int get_token (int /*<<< orphan*/ ,char*,char*) ; 
 int match_token (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 
 int table_do_create (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ table_flush (int /*<<< orphan*/ *) ; 
 scalar_t__ table_get_info (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int table_parse_type (int,char*,scalar_t__*) ; 
 int /*<<< orphan*/  tablenewcmds ; 
 int /*<<< orphan*/  tabletypes ; 
 int /*<<< orphan*/  tablevaltypes ; 

__attribute__((used)) static void
table_create(ipfw_obj_header *oh, int ac, char *av[])
{
	ipfw_xtable_info xi, xie;
	int error, missing, orflush, tcmd, val;
	uint32_t fset, fclear;
	char *e, *p;
	char tbuf[128];

	missing = orflush = 0;
	memset(&xi, 0, sizeof(xi));
	while (ac > 0) {
		tcmd = get_token(tablenewcmds, *av, "option");
		ac--; av++;

		switch (tcmd) {
		case TOK_LIMIT:
			NEED1("limit value required");
			xi.limit = strtol(*av, NULL, 10);
			ac--; av++;
			break;
		case TOK_TYPE:
			NEED1("table type required");
			/* Type may have suboptions after ':' */
			if ((p = strchr(*av, ':')) != NULL)
				*p++ = '\0';
			val = match_token(tabletypes, *av);
			if (val == -1) {
				concat_tokens(tbuf, sizeof(tbuf), tabletypes,
				    ", ");
				errx(EX_USAGE,
				    "Unknown tabletype: %s. Supported: %s",
				    *av, tbuf);
			}
			xi.type = val;
			if (p != NULL) {
				error = table_parse_type(val, p, &xi.tflags);
				if (error != 0)
					errx(EX_USAGE,
					    "Unsupported suboptions: %s", p);
			}
			ac--; av++;
			break;
		case TOK_VALTYPE:
			NEED1("table value type required");
			fset = fclear = 0;
			val = fill_flags(tablevaltypes, *av, &e, &fset, &fclear);
			if (val != -1) {
				xi.vmask = fset;
				ac--; av++;
				break;
			}
			concat_tokens(tbuf, sizeof(tbuf), tablevaltypes, ", ");
			errx(EX_USAGE, "Unknown value type: %s. Supported: %s",
			    e, tbuf);
			break;
		case TOK_ALGO:
			NEED1("table algorithm name required");
			if (strlen(*av) > sizeof(xi.algoname))
				errx(EX_USAGE, "algorithm name too long");
			strlcpy(xi.algoname, *av, sizeof(xi.algoname));
			ac--; av++;
			break;
		case TOK_LOCK:
			xi.flags |= IPFW_TGFLAGS_LOCKED;
			break;
		case TOK_ORFLUSH:
			orflush = 1;
			/* FALLTHROUGH */
		case TOK_MISSING:
			missing = 1;
			break;
		}
	}

	/* Set some defaults to preserve compatibility. */
	if (xi.algoname[0] == '\0' && xi.type == 0)
		xi.type = IPFW_TABLE_ADDR;
	if (xi.vmask == 0)
		xi.vmask = IPFW_VTYPE_LEGACY;

	error = table_do_create(oh, &xi);

	if (error == 0)
		return;

	if (errno != EEXIST || missing == 0)
		err(EX_OSERR, "Table creation failed");

	/* Check that existing table is the same we are trying to create */
	if (table_get_info(oh, &xie) != 0)
		err(EX_OSERR, "Existing table check failed");

	if (xi.limit != xie.limit || xi.type != xie.type ||
	    xi.tflags != xie.tflags || xi.vmask != xie.vmask || (
	    xi.algoname[0] != '\0' && strcmp(xi.algoname,
	    xie.algoname) != 0) || xi.flags != xie.flags)
		errx(EX_DATAERR, "The existing table is not compatible "
		    "with one you are creating.");

	/* Flush existing table if instructed to do so */
	if (orflush != 0 && table_flush(oh) != 0)
		err(EX_OSERR, "Table flush on creation failed");
}