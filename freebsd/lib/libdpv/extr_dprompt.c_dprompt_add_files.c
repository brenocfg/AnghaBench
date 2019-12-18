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
typedef  scalar_t__ uint8_t ;
struct dpv_file_node {scalar_t__ length; char* name; char* msg; scalar_t__ status; int /*<<< orphan*/  read; struct dpv_file_node* next; } ;
typedef  int /*<<< orphan*/  pbar ;
typedef  enum dprompt_state { ____Placeholder_dprompt_state } dprompt_state ;

/* Variables and functions */
#define  DPROMPT_CUSTOM_MSG 134 
#define  DPROMPT_DETAILS 133 
#define  DPROMPT_END_STATE 132 
#define  DPROMPT_MINIMAL 131 
#define  DPROMPT_NONE 130 
#define  DPROMPT_PBAR 129 
#define  DPROMPT_PENDING 128 
 scalar_t__ DPV_STATUS_FAILED ; 
 scalar_t__ DPV_STATUS_RUNNING ; 
 scalar_t__ FALSE ; 
 int FLABEL_MAX ; 
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int HN_DIVISOR_1000 ; 
 int HN_NOSPACE ; 
 int /*<<< orphan*/  PROMPT_MAX ; 
 scalar_t__ TRUE ; 
 char* dialog_prompt_lastline (char*,int) ; 
 scalar_t__ dialog_prompt_nlstate (int /*<<< orphan*/ ) ; 
 scalar_t__ dialog_prompt_numlines (char*,scalar_t__) ; 
 scalar_t__ dialog_test ; 
 int display_limit ; 
 char* done ; 
 int done_lsize ; 
 int done_rsize ; 
 int /*<<< orphan*/  dprompt_add (char const*,...) ; 
 int /*<<< orphan*/  dwidth ; 
 char* fail ; 
 int fail_lsize ; 
 int fail_rsize ; 
 int fheight ; 
 char* gauge_color ; 
 int /*<<< orphan*/  humanize_number (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int label_size ; 
 int mesg_lsize ; 
 int mesg_rsize ; 
 int mesg_size ; 
 char* msg ; 
 scalar_t__ no_labels ; 
 int pbar_size ; 
 char* pct_lsize ; 
 int /*<<< orphan*/  pct_rsize ; 
 int /*<<< orphan*/  pend ; 
 int /*<<< orphan*/  pend_lsize ; 
 int /*<<< orphan*/  pend_rsize ; 
 int /*<<< orphan*/  pprompt ; 
 int snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  spin_char () ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ use_color ; 
 scalar_t__ use_colors ; 
 scalar_t__ use_dialog ; 
 scalar_t__ use_libdialog ; 
 scalar_t__ use_shadow ; 

__attribute__((used)) static int
dprompt_add_files(struct dpv_file_node *file_list,
    struct dpv_file_node *curfile, int pct)
{
	char c;
	char bold_code = 'b'; /* default: enabled */
	char color_code = '4'; /* default: blue */
	uint8_t after_curfile = curfile != NULL ? FALSE : TRUE;
	uint8_t nls = 0;
	char *cp;
	char *lastline;
	char *name;
	const char *bg_code;
	const char *estext;
	const char *format;
	enum dprompt_state dstate;
	int estext_lsize;
	int estext_rsize;
	int flabel_size;
	int hlen;
	int lsize;
	int nlines = 0;
	int nthfile = 0;
	int pwidth;
	int rsize;
	struct dpv_file_node *fp;
	char flabel[FLABEL_MAX + 1];
	char human[32];
	char pbar[pbar_size + 16]; /* +15 for optional color */
	char pbar_cap[sizeof(pbar)];
	char pbar_fill[sizeof(pbar)];


	/* Override color defaults with that of main progress bar */
	if (use_colors || use_shadow) { /* NB: shadow enables color */
		color_code = gauge_color[0];
		/* NB: str[1] aka bg is unused */
		bold_code = gauge_color[2];
	}

	/*
	 * Create mini-progressbar for current file (if applicable)
	 */
	*pbar = '\0';
	if (pbar_size >= 0 && pct >= 0 && curfile != NULL &&
	    (curfile->length >= 0 || dialog_test)) {
		snprintf(pbar, pbar_size + 1, "%*s%3u%%%*s", pct_lsize, "",
		    pct, pct_rsize, "");
		if (use_color) {
			/* Calculate the fill-width of progressbar */
			pwidth = pct * pbar_size / 100;
			/* Round up based on one-tenth of a percent */
			if ((pct * pbar_size % 100) > 50)
				pwidth++;

			/*
			 * Make two copies of pbar. Make one represent the fill
			 * and the other the remainder (cap). We'll insert the
			 * ANSI delimiter in between.
			 */
			*pbar_fill = '\0';
			*pbar_cap = '\0';
			strncat(pbar_fill, (const char *)(pbar), dwidth);
			*(pbar_fill + pwidth) = '\0';
			strncat(pbar_cap, (const char *)(pbar+pwidth), dwidth);

			/* Finalize the mini [color] progressbar */
			snprintf(pbar, sizeof(pbar),
			    "\\Z%c\\Zr\\Z%c%s%s%s\\Zn", bold_code, color_code,
			    pbar_fill, "\\ZR", pbar_cap);
		}
	}

	for (fp = file_list; fp != NULL; fp = fp->next) {
		flabel_size = label_size;
		name = fp->name;
		nthfile++;

		/*
		 * Support multiline filenames (where the filename is taken as
		 * the last line and the text leading up to the last line can
		 * be used as (for example) a heading/separator between files.
		 */
		if (use_dialog)
			nls = dialog_prompt_nlstate(pprompt);
		nlines += dialog_prompt_numlines(name, nls);
		lastline = dialog_prompt_lastline(name, 1);
		if (name != lastline) {
			c = *lastline;
			*lastline = '\0';
			dprompt_add("%s", name);
			*lastline = c;
			name = lastline;
		}

		/* Support color codes (for dialog(1,3)) in file names */
		if ((use_dialog || use_libdialog) && use_color) {
			cp = name;
			while (*cp != '\0') {
				if (*cp == '\\' && *(cp + 1) != '\0' &&
				    *(++cp) == 'Z' && *(cp + 1) != '\0') {
					cp++;
					flabel_size += 3;
				}
				cp++;
			}
			if (flabel_size > FLABEL_MAX)
				flabel_size = FLABEL_MAX;
		}

		/* If no mini-progressbar, increase label width */
		if (pbar_size < 0 && flabel_size <= FLABEL_MAX - 2 &&
		    no_labels == FALSE)
			flabel_size += 2;

		/* If name is too long, add an ellipsis */
		if (snprintf(flabel, flabel_size + 1, "%s", name) >
		    flabel_size) sprintf(flabel + flabel_size - 3, "...");

		/*
		 * Append the label (processing the current file differently)
		 */
		if (fp == curfile && pct < 100) {
			/*
			 * Add an ellipsis to current file name if it will fit.
			 * There may be an ellipsis already from truncating the
			 * label (in which case, we already have one).
			 */
			cp = flabel + strlen(flabel);
			if (cp < (flabel + flabel_size))
				snprintf(cp, flabel_size -
				    (cp - flabel) + 1, "...");

			/* Append label (with spinner and optional color) */
			dprompt_add("%s%-*s%s %c", use_color ? "\\Zb" : "",
			    flabel_size, flabel, use_color ? "\\Zn" : "",
			    spin_char());
		} else
			dprompt_add("%-*s%s %s", flabel_size,
			    flabel, use_color ? "\\Zn" : "", " ");

		/*
		 * Append pbar/status (processing the current file differently)
		 */
		dstate = DPROMPT_NONE;
		if (fp->msg != NULL)
			dstate = DPROMPT_CUSTOM_MSG;
		else if (pbar_size < 0)
			dstate = DPROMPT_NONE;
		else if (pbar_size < 4)
			dstate = DPROMPT_MINIMAL;
		else if (after_curfile)
			dstate = DPROMPT_PENDING;
		else if (fp == curfile) {
			if (*pbar == '\0') {
				if (fp->length < 0)
					dstate = DPROMPT_DETAILS;
				else if (fp->status == DPV_STATUS_RUNNING)
					dstate = DPROMPT_DETAILS;
				else
					dstate = DPROMPT_END_STATE;
			}
			else if (dialog_test) /* status/length ignored */
				dstate = pct < 100 ?
				    DPROMPT_PBAR : DPROMPT_END_STATE;
			else if (fp->status == DPV_STATUS_RUNNING)
				dstate = fp->length < 0 ?
				    DPROMPT_DETAILS : DPROMPT_PBAR;
			else /* not running */
				dstate = fp->length < 0 ?
				    DPROMPT_DETAILS : DPROMPT_END_STATE;
		} else { /* before curfile */
			if (dialog_test)
				dstate = DPROMPT_END_STATE;
			else
				dstate = fp->length < 0 ?
				    DPROMPT_DETAILS : DPROMPT_END_STATE;
		}
		format = use_color ?
		    " [\\Z%c%s%-*s%s%-*s\\Zn]\\n" :
		    " [%-*s%s%-*s]\\n";
		if (fp->status == DPV_STATUS_FAILED) {
			bg_code = "\\Zr\\Z1"; /* Red */
			estext_lsize = fail_lsize;
			estext_rsize = fail_rsize;
			estext = fail;
		} else { /* e.g., DPV_STATUS_DONE */
			bg_code = "\\Zr\\Z2"; /* Green */
			estext_lsize = done_lsize;
			estext_rsize = done_rsize;
			estext = done;
		}
		switch (dstate) {
		case DPROMPT_PENDING: /* Future file(s) */
			dprompt_add(" [%-*s%s%-*s]\\n",
			    pend_lsize, "", pend, pend_rsize, "");
			break;
		case DPROMPT_PBAR: /* Current file */
			dprompt_add(" [%s]\\n", pbar);
			break;
		case DPROMPT_END_STATE: /* Past/Current file(s) */
			if (use_color)
				dprompt_add(format, bold_code, bg_code,
				    estext_lsize, "", estext,
				    estext_rsize, "");
			else
				dprompt_add(format,
				    estext_lsize, "", estext,
				    estext_rsize, "");
			break;
		case DPROMPT_DETAILS: /* Past/Current file(s) */
			humanize_number(human, pbar_size + 2, fp->read, "",
			    HN_AUTOSCALE, HN_NOSPACE | HN_DIVISOR_1000);

			/* Calculate center alignment */
			hlen = (int)strlen(human);
			lsize = (pbar_size - hlen) / 2;
			rsize = lsize;
			if ((lsize+hlen+rsize) != pbar_size)
				rsize++;

			if (use_color)
				dprompt_add(format, bold_code, bg_code,
				    lsize, "", human, rsize, "");
			else
				dprompt_add(format,
				    lsize, "", human, rsize, "");
			break;
		case DPROMPT_CUSTOM_MSG: /* File-specific message override */
			snprintf(msg, PROMPT_MAX + 1, "%s", fp->msg);
			if (pbar_size < (mesg_size = strlen(msg))) {
				mesg_lsize = mesg_rsize = 0;
				*(msg + pbar_size) = '\0';
				mesg_size = pbar_size;
			} else {
				mesg_lsize = (pbar_size - mesg_size) / 2;
				mesg_rsize = mesg_lsize;
				if ((mesg_rsize + mesg_size + mesg_lsize)
				    != pbar_size)
					mesg_rsize++;
			}
			if (use_color)
				dprompt_add(format, bold_code, bg_code,
				    mesg_lsize, "", msg, mesg_rsize, "");
			else
				dprompt_add(format, mesg_lsize, "", msg,
				    mesg_rsize, "");
			break;
		case DPROMPT_MINIMAL: /* Short progress bar, minimal room */
			if (use_color)
				dprompt_add(format, bold_code, bg_code,
				    pbar_size, "", "", 0, "");
			else
				dprompt_add(format, pbar_size, "", "", 0, "");
			break;
		case DPROMPT_NONE: /* pbar_size < 0 */
			/* FALLTHROUGH */
		default:
			dprompt_add(" \\n");
			/*
			 * NB: Leading space required for the case when
			 * spin_char() returns a single backslash [\] which
			 * without the space, changes the meaning of `\n'
			 */
		}

		/* Stop building if we've hit the internal limit */
		if (nthfile >= display_limit)
			break;

		/* If this is the current file, all others are pending */
		if (fp == curfile)
			after_curfile = TRUE;
	}

	/*
	 * Since we cannot change the height/width of the [X]dialog(1) widget
	 * after spawn, to make things look nice let's pad the height so that
	 * the `-a text' always appears in the same spot.
	 *
	 * NOTE: fheight is calculated in dprompt_init(). It represents the
	 * maximum height required to display the set of items (broken up into
	 * pieces of display_limit chunks) whose names contain the most
	 * newlines for any given set.
	 */
	while (nlines < fheight) {
		dprompt_add("\n");
		nlines++;
	}

	return (nthfile);
}