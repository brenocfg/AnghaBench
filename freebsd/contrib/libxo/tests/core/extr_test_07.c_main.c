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

/* Variables and functions */
 int /*<<< orphan*/  XOF_COLUMNS ; 
 int /*<<< orphan*/  info ; 
 int /*<<< orphan*/  info_count ; 
 int /*<<< orphan*/  xo_attr (char*,char*,char*) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 
 int xo_parse_args (int,char**) ; 
 int /*<<< orphan*/  xo_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_set_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main (int argc, char **argv)
{
    struct employee {
	const char *e_first;
	const char *e_nic;
	const char *e_last;
	unsigned e_dept;
	unsigned e_percent;
    } employees[] = {
	{ "Jim", "რეგტ", "გთხოვთ ახ", 431, 90 },
	{ "Terry", "<one", "Οὐχὶ ταὐτὰ παρίσταταί μοι Jones", 660, 90 },
	{ "Leslie", "Les", "Patterson", 341,60 },
	{ "Ashley", "Ash", "Meter & Smith", 1440, 40 },
	{ "0123456789", "0123456789", "012345678901234567890", 1440, 40 },
	{ "ახლა", "გაიარო", "საერთაშორისო", 123, 90 },
	{ NULL, NULL }
    }, *ep = employees;
    int rc;

    argc = xo_parse_args(argc, argv);
    if (argc < 0)
	return 1;

    xo_set_info(NULL, info, info_count);
    xo_set_flags(NULL, XOF_COLUMNS);

    xo_open_container("employees");

    xo_open_list("test");
    xo_open_instance("test");
    xo_emit("{ek:filename/%s}", NULL);
    xo_close_instance("test");
    xo_close_list("test");

    rc = xo_emit("Οὐχὶ ταὐτὰ παρίσταταί μοι {:v1/%s}, {:v2/%s}\n",
	    "γιγνώσκειν", "ὦ ἄνδρες ᾿Αθηναῖοι");
    rc = xo_emit("{:columns/%d}\n", rc);
    xo_emit("{:columns/%d}\n", rc);

    rc = xo_emit("გთხოვთ {:v1/%s} {:v2/%s}\n",
	    "ახლავე გაიაროთ რეგისტრაცია",
	    "Unicode-ის მეათე საერთაშორისო");
    xo_emit("{:columns/%d}\n", rc);


    rc = xo_emit("{T:First Name/%-25s}{T:Last Name/%-14s}"
	    "{T:/%-12s}{T:Time (%)}\n", "Department");
    xo_emit("{:columns/%d}\n", rc);

    xo_open_list("employee");
    for ( ; ep->e_first; ep++) {
	xo_open_instance("employee");
	rc = xo_emit("{[:-25}{:first-name/%s} ({:nic-name/\"%s\"}){]:}"
		"{:last-name/%-14..14s/%s}"
		"{:department/%8u/%u}{:percent-time/%8u/%u}\n",
		ep->e_first, ep->e_nic, ep->e_last, ep->e_dept, ep->e_percent);
	xo_emit("{:columns/%d}\n", rc);
	if (ep->e_percent > 50) {
	    xo_attr("full-time", "%s", "honest & for true");
	    xo_emit("{e:benefits/%s}", "full");
	}
	xo_close_instance("employee");
    }

    xo_close_list("employee");
    xo_close_container("employees");

    xo_finish();

    return 0;
}