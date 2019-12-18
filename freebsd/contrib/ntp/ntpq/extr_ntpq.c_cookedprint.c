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
typedef  int u_long ;
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  l_fp ;
typedef  int /*<<< orphan*/  bv ;
typedef  int /*<<< orphan*/  bn ;
typedef  int /*<<< orphan*/  b ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  AR 136 
#define  FX 135 
#define  HA 134 
 int /*<<< orphan*/  ISREFCLOCKADR (int /*<<< orphan*/ *) ; 
#define  LP 133 
 int MAXVALLEN ; 
 int MAXVARLEN ; 
#define  NA 132 
#define  OC 131 
#define  PADDING 130 
#define  RF 129 
#define  TS 128 
 int /*<<< orphan*/  UNUSED_ARG (int) ; 
 int /*<<< orphan*/  atoascii (char*,int,char*,int) ; 
 int /*<<< orphan*/  decodearr (char*,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decodenetnum (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decodets (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decodeuint (char*,int*) ; 
 int /*<<< orphan*/  endoutput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ nextvar (size_t*,char const**,char**,char**) ; 
 char* nntohost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  outputarr (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 char* prettydate (int /*<<< orphan*/ *) ; 
 char* refnumtoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  startoutput () ; 
 char* statustoa (int,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* stoa (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 char* tstflags (int) ; 
 int varfmt (char*) ; 

__attribute__((used)) static void
cookedprint(
	int datatype,
	size_t length,
	const char *data,
	int status,
	int quiet,
	FILE *fp
	)
{
	char *name;
	char *value;
	char output_raw;
	int fmt;
	l_fp lfp;
	sockaddr_u hval;
	u_long uval;
	int narr;
	size_t len;
	l_fp lfparr[8];
	char b[12];
	char bn[2 * MAXVARLEN];
	char bv[2 * MAXVALLEN];

	UNUSED_ARG(datatype);

	if (!quiet)
		fprintf(fp, "status=%04x %s,\n", status,
			statustoa(datatype, status));

	startoutput();
	while (nextvar(&length, &data, &name, &value)) {
		fmt = varfmt(name);
		output_raw = 0;
		switch (fmt) {

		case PADDING:
			output_raw = '*';
			break;

		case TS:
			if (!value || !decodets(value, &lfp))
				output_raw = '?';
			else
				output(fp, name, prettydate(&lfp));
			break;

		case HA:	/* fallthru */
		case NA:
			if (!value || !decodenetnum(value, &hval)) {
				output_raw = '?';
			} else if (fmt == HA){
				output(fp, name, nntohost(&hval));
			} else {
				output(fp, name, stoa(&hval));
			}
			break;

		case RF:
			if (!value) {
				output_raw = '?';
			} else if (decodenetnum(value, &hval)) {
				if (ISREFCLOCKADR(&hval))
					output(fp, name,
					       refnumtoa(&hval));
				else
					output(fp, name, stoa(&hval));
			} else if (strlen(value) <= 4) {
				output(fp, name, value);
			} else {
				output_raw = '?';
			}
			break;

		case LP:
			if (!value || !decodeuint(value, &uval) || uval > 3) {
				output_raw = '?';
			} else {
				b[0] = (0x2 & uval)
					   ? '1'
					   : '0';
				b[1] = (0x1 & uval)
					   ? '1'
					   : '0';
				b[2] = '\0';
				output(fp, name, b);
			}
			break;

		case OC:
			if (!value || !decodeuint(value, &uval)) {
				output_raw = '?';
			} else {
				snprintf(b, sizeof(b), "%03lo", uval);
				output(fp, name, b);
			}
			break;

		case AR:
			if (!value || !decodearr(value, &narr, lfparr, 8))
				output_raw = '?';
			else
				outputarr(fp, name, narr, lfparr);
			break;

		case FX:
			if (!value || !decodeuint(value, &uval))
				output_raw = '?';
			else
				output(fp, name, tstflags(uval));
			break;

		default:
			fprintf(stderr, "Internal error in cookedprint, %s=%s, fmt %d\n",
				name, value, fmt);
			output_raw = '?';
			break;
		}

		if (output_raw != 0) {
			/* TALOS-CAN-0063: avoid buffer overrun */
			atoascii(name, MAXVARLEN, bn, sizeof(bn));
			if (output_raw != '*') {
				atoascii(value, MAXVALLEN,
					 bv, sizeof(bv) - 1);
				len = strlen(bv);
				bv[len] = output_raw;
				bv[len+1] = '\0';
			} else {
				atoascii(value, MAXVALLEN,
					 bv, sizeof(bv));
			}
			output(fp, bn, bv);
		}
	}
	endoutput(fp);
}