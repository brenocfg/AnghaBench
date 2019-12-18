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
typedef  int /*<<< orphan*/  xo_handle_t ;
typedef  int ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  c_flags; } ;
typedef  TYPE_1__ csv_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  CF_DEBUG ; 
 int /*<<< orphan*/  CF_DOS_NEWLINE ; 
 int /*<<< orphan*/  CF_HAS_PATH ; 
 int /*<<< orphan*/  CF_NO_HEADER ; 
 int /*<<< orphan*/  CF_NO_KEYS ; 
 int /*<<< orphan*/  CF_NO_QUOTES ; 
 int /*<<< orphan*/  CF_VALUE_ONLY ; 
 char* alloca (int) ; 
 scalar_t__ csv_record_leafs (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 scalar_t__ csv_record_path (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ xo_streq (char*,char*) ; 
 int /*<<< orphan*/  xo_warn_hc (int /*<<< orphan*/ *,int,char*,char*) ; 

__attribute__((used)) static int
csv_options (xo_handle_t *xop, csv_private_t *csv, const char *raw_opts)
{
    ssize_t len = strlen(raw_opts);
    char *options = alloca(len + 1);
    memcpy(options, raw_opts, len);
    options[len] = '\0';

    char *cp, *ep, *np, *vp;
    for (cp = options, ep = options + len + 1; cp && cp < ep; cp = np) {
	np = strchr(cp, '+');
	if (np)
	    *np++ = '\0';

	vp = strchr(cp, '=');
	if (vp)
	    *vp++ = '\0';

	if (xo_streq(cp, "path")) {
	    /* Record the path */
	    if (vp != NULL && csv_record_path(xop, csv, vp))
  		return -1;

	    csv->c_flags |= CF_HAS_PATH; /* Yup, we have an explicit path now */

	} else if (xo_streq(cp, "leafs")
		   || xo_streq(cp, "leaf")
		   || xo_streq(cp, "leaves")) {
	    /* Record the leafs */
	    if (vp != NULL && csv_record_leafs(xop, csv, vp))
  		return -1;

	} else if (xo_streq(cp, "no-keys")) {
	    csv->c_flags |= CF_NO_KEYS;
	} else if (xo_streq(cp, "no-header")) {
	    csv->c_flags |= CF_NO_HEADER;
	} else if (xo_streq(cp, "value-only")) {
	    csv->c_flags |= CF_VALUE_ONLY;
	} else if (xo_streq(cp, "dos")) {
	    csv->c_flags |= CF_DOS_NEWLINE;
	} else if (xo_streq(cp, "no-quotes")) {
	    csv->c_flags |= CF_NO_QUOTES;
	} else if (xo_streq(cp, "debug")) {
	    csv->c_flags |= CF_DEBUG;
	} else {
	    xo_warn_hc(xop, -1,
		       "unknown encoder option value: '%s'", cp);
	    return -1;
	}
    }

    return 0;
}