#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_2__ {int report_ID; int kind; } ;
struct variable {char* name; TYPE_1__ h; struct variable* next; } ;
typedef  int /*<<< orphan*/  report_desc_t ;
typedef  enum hid_kind { ____Placeholder_hid_kind } hid_kind ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int hid_feature ; 
 int hid_get_report (int,int,int*,int) ; 
 int /*<<< orphan*/  hid_get_report_id (int) ; 
 int hid_input ; 
 int hid_output ; 
 int hid_report_size (int /*<<< orphan*/ ,int,int) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  noname ; 
 int /*<<< orphan*/  prdata (int*,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,int*,int) ; 
 struct variable* vars ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warn (char*,int) ; 
 scalar_t__ zflag ; 

__attribute__((used)) static void
dumpdata(int f, report_desc_t rd, int loop)
{
	struct variable *var;
	int dlen, havedata, i, match, r, rid, use_rid;
	u_char *dbuf;
	enum hid_kind kind;

	kind = zflag ? 3 : 0;
	rid = -1;
	use_rid = !!hid_get_report_id(f);
	do {
		if (kind < 3) {
			if (++rid >= 256) {
				rid = 0;
				kind++;
			}
			if (kind >= 3)
				rid = -1;
			for (var = vars; var; var = var->next) {
				if (rid == var->h.report_ID &&
				    kind == var->h.kind)
					break;
			}
			if (var == NULL)
				continue;
		}
		dlen = hid_report_size(rd, kind < 3 ? kind : hid_input, rid);
		if (dlen <= 0)
			continue;
		dbuf = malloc(dlen);
		memset(dbuf, 0, dlen);
		if (kind < 3) {
			dbuf[0] = rid;
			r = hid_get_report(f, kind, dbuf, dlen);
			if (r < 0)
				warn("hid_get_report(rid %d)", rid);
			havedata = !r && (rid == 0 || dbuf[0] == rid);
			if (rid != 0)
				dbuf[0] = rid;
		} else {
			r = read(f, dbuf, dlen);
			if (r < 1)
				err(1, "read error");
			havedata = 1;
		}
		if (verbose) {
			printf("Got %s report %d (%d bytes):",
			    kind == hid_output ? "output" :
			    kind == hid_feature ? "feature" : "input",
			    use_rid ? dbuf[0] : 0, dlen);
			if (havedata) {
				for (i = 0; i < dlen; i++)
					printf(" %02x", dbuf[i]);
			}
			printf("\n");
		}
		match = 0;
		for (var = vars; var; var = var->next) {
			if ((kind < 3 ? kind : hid_input) != var->h.kind)
				continue;
			if (var->h.report_ID != 0 &&
			    dbuf[0] != var->h.report_ID)
				continue;
			match = 1;
			if (!noname)
				printf("%s=", var->name);
			if (havedata)
				prdata(dbuf, &var->h);
			printf("\n");
		}
		if (match)
			printf("\n");
		free(dbuf);
	} while (loop || kind < 3);
}