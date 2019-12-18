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
typedef  int /*<<< orphan*/  u_short ;
typedef  scalar_t__ u_int ;
struct parse {int dummy; } ;
struct TYPE_5__ {char* flagstr; int /*<<< orphan*/  mask; scalar_t__ hits; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ reslist_row ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int COUNTOF (char const*) ; 
 int /*<<< orphan*/  CTL_OP_READ_ORDLIST_A ; 
 int FALSE ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int RESLIST_FIELDS ; 
 int TRUE ; 
 int /*<<< orphan*/  ZERO (TYPE_1__) ; 
 int /*<<< orphan*/  another_reslist_field (int*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int debug ; 
 int /*<<< orphan*/  decodenetnum (char*,int /*<<< orphan*/ *) ; 
 int doquery (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const,char const*,int /*<<< orphan*/ *,size_t*,char const**) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 scalar_t__ nextvar (size_t*,char const**,char**,char**) ; 
 int sscanf (char*,char const*,scalar_t__*) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  validate_reslist_idx (int /*<<< orphan*/ *,scalar_t__,int*,TYPE_1__*) ; 

__attribute__((used)) static void 
reslist(
	struct parse *	pcmd,
	FILE *		fp
	)
{
	const char addr_fmtu[] =	"addr.%u";
	const char mask_fmtu[] =	"mask.%u";
	const char hits_fmt[] =		"hits.%u";
	const char flags_fmt[] =	"flags.%u";
	const char qdata[] =		"addr_restrictions";
	const int qdata_chars =		COUNTOF(qdata) - 1;
	const char *	datap;
	int		qres;
	size_t		dsize;
	u_short		rstatus;
	char *		tag;
	char *		val;
	int		fields;
	u_int		ui;
	reslist_row	row;
	int		comprende;
	size_t		len;

	qres = doquery(CTL_OP_READ_ORDLIST_A, 0, TRUE, qdata_chars,
		       qdata, &rstatus, &dsize, &datap);
	if (qres)	/* message already displayed */
		return;

	fprintf(fp,
		"   hits    addr/prefix or addr mask\n"
		"           restrictions\n"
		"==============================================================================\n");
		/* '=' x 78 */

	ZERO(row);
	fields = 0;
	ui = 0;
	while (nextvar(&dsize, &datap, &tag, &val)) {
		INSIST(tag && val);
		if (debug > 1)
			fprintf(stderr, "nextvar gave: %s = %s\n", tag, val);
		comprende = FALSE;
		switch(tag[0]) {

		case 'a':
			if (1 == sscanf(tag, addr_fmtu, &ui) &&
			    decodenetnum(val, &row.addr))
				comprende = TRUE;
			break;

		case 'f':
			if (1 == sscanf(tag, flags_fmt, &ui)) {
				if (NULL == val) {
					row.flagstr[0] = '\0';
					comprende = TRUE;
				} else if ((len = strlen(val)) < sizeof(row.flagstr)) {
					memcpy(row.flagstr, val, len);
					row.flagstr[len] = '\0';
					comprende = TRUE;
				} else {
					 /* no flags, and still !comprende */
					row.flagstr[0] = '\0';
				}
			}
			break;

		case 'h':
			if (1 == sscanf(tag, hits_fmt, &ui) &&
			    1 == sscanf(val, "%lu", &row.hits))
				comprende = TRUE;
			break;

		case 'm':
			if (1 == sscanf(tag, mask_fmtu, &ui) &&
			    decodenetnum(val, &row.mask))
				comprende = TRUE;
			break;
		}

		if (comprende) {
			/* error out if rows out of order */
			validate_reslist_idx(fp, ui, &fields, &row);
			/* if the row is complete, print it */
			another_reslist_field(&fields, &row, fp);
		}
	}
	if (fields != RESLIST_FIELDS)
		fprintf(fp, "Warning: incomplete row with %d (of %d) fields",
			fields, RESLIST_FIELDS);

	fflush(fp);
}