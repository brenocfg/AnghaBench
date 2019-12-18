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
 int /*<<< orphan*/  CF_LEAFS_DONE ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  csv_dbg (int /*<<< orphan*/ *,TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  csv_leaf_num (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
csv_record_leafs (xo_handle_t *xop, csv_private_t *csv, const char *leafs_raw)
{
    char *cp, *ep, *np;
    ssize_t len = strlen(leafs_raw);
    char *leafs_buf = alloca(len + 1);

    memcpy(leafs_buf, leafs_raw, len + 1); /* Make local copy */

    for (cp = leafs_buf, ep = leafs_buf + len; cp && cp < ep; cp = np) {
	np = strchr(cp, '.');
	if (np)
	    *np++ = '\0';

	if (*cp == '\0')		/* Skip empty names */
	    continue;

	csv_dbg(xop, csv, "adding leaf: [%s]\n", cp);
	csv_leaf_num(xop, csv, cp, 0);
    }

    /*
     * Since we've been told explicitly what leafs matter, ignore the rest
     */
    csv->c_flags |= CF_LEAFS_DONE;

    return 0;
}