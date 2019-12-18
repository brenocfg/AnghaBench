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
struct hid_item {int kind; int usage; int flags; int usage_minimum; int usage_maximum; } ;
struct hid_data {int dummy; } ;
struct command {int line; int anyvalue; int value; int debounce; int lastseen; int lastused; char* action; void* name; struct hid_item item; struct command* next; } ;
typedef  int /*<<< orphan*/  report_desc_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  HID_PAGE (int) ; 
 int HIO_CONST ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int SIZE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  freecommands (struct command*) ; 
#define  hid_collection 130 
 int /*<<< orphan*/  hid_end_parse (struct hid_data*) ; 
#define  hid_endcollection 129 
 scalar_t__ hid_get_item (struct hid_data*,struct hid_item*) ; 
#define  hid_input 128 
 struct hid_data* hid_start_parse (int /*<<< orphan*/ ,int,int) ; 
 char* hid_usage_in_page (int) ; 
 char* hid_usage_page (int /*<<< orphan*/ ) ; 
 scalar_t__ isdemon ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 struct command* malloc (int) ; 
 int /*<<< orphan*/  peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 int sscanf (char*,char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * strrchr (char*,char) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,int,char*) ; 
 int verbose ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

struct command *
parse_conf(const char *conf, report_desc_t repd, int reportid, int ignore)
{
	FILE *f;
	char *p;
	int line;
	char buf[SIZE], name[SIZE], value[SIZE], debounce[SIZE], action[SIZE];
	char usbuf[SIZE], coll[SIZE], *tmp;
	struct command *cmd, *cmds;
	struct hid_data *d;
	struct hid_item h;
	int inst, cinst, u, lo, hi, range, t;

	f = fopen(conf, "r");
	if (f == NULL)
		err(1, "%s", conf);

	cmds = NULL;
	for (line = 1; ; line++) {
		if (fgets(buf, sizeof buf, f) == NULL)
			break;
		if (buf[0] == '#' || buf[0] == '\n')
			continue;
		p = strchr(buf, '\n');
		while (p && isspace(peek(f))) {
			if (fgets(p, sizeof buf - strlen(buf), f) == NULL)
				break;
			p = strchr(buf, '\n');
		}
		if (p)
			*p = 0;
		if (sscanf(buf, "%s %s %s %[^\n]",
			   name, value, debounce, action) != 4) {
			if (isdemon) {
				syslog(LOG_WARNING, "config file `%s', line %d"
				       ", syntax error: %s", conf, line, buf);
				freecommands(cmds);
				return (NULL);
			} else {
				errx(1, "config file `%s', line %d,"
				     ", syntax error: %s", conf, line, buf);
			}
		}
		tmp = strchr(name, '#');
		if (tmp != NULL) {
			*tmp = 0;
			inst = atoi(tmp + 1);
		} else
			inst = 0;

		cmd = malloc(sizeof *cmd);
		if (cmd == NULL)
			err(1, "malloc failed");
		cmd->next = cmds;
		cmds = cmd;
		cmd->line = line;

		if (strcmp(value, "*") == 0) {
			cmd->anyvalue = 1;
		} else {
			cmd->anyvalue = 0;
			if (sscanf(value, "%d", &cmd->value) != 1) {
				if (isdemon) {
					syslog(LOG_WARNING,
					       "config file `%s', line %d, "
					       "bad value: %s (should be * or a number)\n",
					       conf, line, value);
					freecommands(cmds);
					return (NULL);
				} else {
					errx(1, "config file `%s', line %d, "
					     "bad value: %s (should be * or a number)\n",
					     conf, line, value);
				}
			}
		}

		if (sscanf(debounce, "%d", &cmd->debounce) != 1) {
			if (isdemon) {
				syslog(LOG_WARNING,
				       "config file `%s', line %d, "
				       "bad value: %s (should be a number >= 0)\n",
				       conf, line, debounce);
				freecommands(cmds);
				return (NULL);
			} else {
				errx(1, "config file `%s', line %d, "
				     "bad value: %s (should be a number >= 0)\n",
				     conf, line, debounce);
			}
		}

		coll[0] = 0;
		cinst = 0;
		for (d = hid_start_parse(repd, 1 << hid_input, reportid);
		     hid_get_item(d, &h); ) {
			if (verbose > 2)
				printf("kind=%d usage=%x\n", h.kind, h.usage);
			if (h.flags & HIO_CONST)
				continue;
			switch (h.kind) {
			case hid_input:
				if (h.usage_minimum != 0 ||
				    h.usage_maximum != 0) {
					lo = h.usage_minimum;
					hi = h.usage_maximum;
					range = 1;
				} else {
					lo = h.usage;
					hi = h.usage;
					range = 0;
				}
				for (u = lo; u <= hi; u++) {
					if (coll[0]) {
						snprintf(usbuf, sizeof usbuf,
						  "%s.%s:%s", coll+1,
						  hid_usage_page(HID_PAGE(u)),
						  hid_usage_in_page(u));
					} else {
						snprintf(usbuf, sizeof usbuf,
						  "%s:%s",
						  hid_usage_page(HID_PAGE(u)),
						  hid_usage_in_page(u));
					}
					if (verbose > 2)
						printf("usage %s\n", usbuf);
					t = strlen(usbuf) - strlen(name);
					if (t > 0) {
						if (strcmp(usbuf + t, name))
							continue;
						if (usbuf[t - 1] != '.')
							continue;
					} else if (strcmp(usbuf, name))
						continue;
					if (inst == cinst++)
						goto foundhid;
				}
				break;
			case hid_collection:
				snprintf(coll + strlen(coll),
				    sizeof coll - strlen(coll),  ".%s:%s",
				    hid_usage_page(HID_PAGE(h.usage)), 
				    hid_usage_in_page(h.usage));
				break;
			case hid_endcollection:
				if (coll[0])
					*strrchr(coll, '.') = 0;
				break;
			default:
				break;
			}
		}
		if (ignore) {
			if (verbose)
				warnx("ignore item '%s'", name);
			continue;
		}
		if (isdemon) {
			syslog(LOG_WARNING, "config file `%s', line %d, HID "
			       "item not found: `%s'\n", conf, line, name);
			freecommands(cmds);
			return (NULL);
		} else {
			errx(1, "config file `%s', line %d, HID item "
			     "not found: `%s'\n", conf, line, name);
		}

	foundhid:
		hid_end_parse(d);
		cmd->lastseen = -1;
		cmd->lastused = -1;
		cmd->item = h;
		cmd->name = strdup(name);
		cmd->action = strdup(action);
		if (range) {
			if (cmd->value == 1)
				cmd->value = u - lo;
			else
				cmd->value = -1;
		}

		if (verbose)
			printf("PARSE:%d %s, %d, '%s'\n", cmd->line, name,
			       cmd->value, cmd->action);
	}
	fclose(f);
	return (cmds);
}