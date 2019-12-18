#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  term_names; void** Strings; } ;
typedef  TYPE_1__ TERMTYPE ;
typedef  int /*<<< orphan*/  PredFunc ;

/* Variables and functions */
 void* ABSENT_STRING ; 
 char* ExtStrname (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int FMT_ENTRY () ; 
 scalar_t__ F_TCONVERR ; 
 scalar_t__ F_TERMCAP ; 
 int MAX_TERMCAP_LENGTH ; 
 int MAX_TERMINFO_LENGTH ; 
 unsigned int NUM_STRINGS (TYPE_1__*) ; 
 int /*<<< orphan*/  SHOW_WHY (char*,...) ; 
 unsigned int STRCOUNT ; 
 int /*<<< orphan*/  STRING ; 
 int /*<<< orphan*/  STR_IDX (void*) ; 
 int TRUE ; 
 scalar_t__ VALID_STRING (void*) ; 
 int V_BSD ; 
 char* _nc_first_name (int /*<<< orphan*/ ) ; 
 void* acs_chars ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 scalar_t__ kill_fkeys (TYPE_1__*,int) ; 
 scalar_t__ kill_labels (TYPE_1__*,int) ; 
 scalar_t__ outform ; 
 scalar_t__ purged_acs (TYPE_1__*) ; 
 void* save_sgr ; 
 void* set_attributes ; 
 int /*<<< orphan*/  set_obsolete_termcaps (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strnames ; 
 int tversion ; 
 int /*<<< orphan*/  version_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dump_entry(TERMTYPE *tterm,
	   int suppress_untranslatable,
	   int limited,
	   int numbers,
	   PredFunc pred)
{
    TERMTYPE save_tterm;
    int len, critlen;
    const char *legend;
    bool infodump;

    if (outform == F_TERMCAP || outform == F_TCONVERR) {
	critlen = MAX_TERMCAP_LENGTH;
	legend = "older termcap";
	infodump = FALSE;
	set_obsolete_termcaps(tterm);
    } else {
	critlen = MAX_TERMINFO_LENGTH;
	legend = "terminfo";
	infodump = TRUE;
    }

    save_sgr = set_attributes;

    if ((FMT_ENTRY() > critlen)
	&& limited) {

	save_tterm = *tterm;
	if (!suppress_untranslatable) {
	    SHOW_WHY("# (untranslatable capabilities removed to fit entry within %d bytes)\n",
		     critlen);
	    suppress_untranslatable = TRUE;
	}
	if (FMT_ENTRY() > critlen) {
	    /*
	     * We pick on sgr because it's a nice long string capability that
	     * is really just an optimization hack.  Another good candidate is
	     * acsc since it is both long and unused by BSD termcap.
	     */
	    bool changed = FALSE;

#if NCURSES_XNAMES
	    /*
	     * Extended names are most likely function-key definitions.  Drop
	     * those first.
	     */
	    unsigned n;
	    for (n = STRCOUNT; n < NUM_STRINGS(tterm); n++) {
		const char *name = ExtStrname(tterm, (int) n, strnames);

		if (VALID_STRING(tterm->Strings[n])) {
		    set_attributes = ABSENT_STRING;
		    /* we remove long names anyway - only report the short */
		    if (strlen(name) <= 2) {
			SHOW_WHY("# (%s removed to fit entry within %d bytes)\n",
				 name,
				 critlen);
		    }
		    changed = TRUE;
		    if (FMT_ENTRY() <= critlen)
			break;
		}
	    }
#endif
	    if (VALID_STRING(set_attributes)) {
		set_attributes = ABSENT_STRING;
		SHOW_WHY("# (sgr removed to fit entry within %d bytes)\n",
			 critlen);
		changed = TRUE;
	    }
	    if (!changed || (FMT_ENTRY() > critlen)) {
		if (purged_acs(tterm)) {
		    acs_chars = ABSENT_STRING;
		    SHOW_WHY("# (acsc removed to fit entry within %d bytes)\n",
			     critlen);
		    changed = TRUE;
		}
	    }
	    if (!changed || (FMT_ENTRY() > critlen)) {
		int oldversion = tversion;

		tversion = V_BSD;
		SHOW_WHY("# (terminfo-only capabilities suppressed to fit entry within %d bytes)\n",
			 critlen);

		len = FMT_ENTRY();
		if (len > critlen
		    && kill_labels(tterm, len - critlen)) {
		    SHOW_WHY("# (some labels capabilities suppressed to fit entry within %d bytes)\n",
			     critlen);
		    len = FMT_ENTRY();
		}
		if (len > critlen
		    && kill_fkeys(tterm, len - critlen)) {
		    SHOW_WHY("# (some function-key capabilities suppressed to fit entry within %d bytes)\n",
			     critlen);
		    len = FMT_ENTRY();
		}
		if (len > critlen) {
		    (void) fprintf(stderr,
				   "warning: %s entry is %d bytes long\n",
				   _nc_first_name(tterm->term_names),
				   len);
		    SHOW_WHY("# WARNING: this entry, %d bytes long, may core-dump %s libraries!\n",
			     len, legend);
		}
		tversion = oldversion;
	    }
	    set_attributes = save_sgr;
	    *tterm = save_tterm;
	}
    } else if (!version_filter(STRING, STR_IDX(acs_chars))) {
	save_tterm = *tterm;
	if (purged_acs(tterm)) {
	    (void) FMT_ENTRY();
	}
	*tterm = save_tterm;
    }
}