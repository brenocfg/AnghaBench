#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ u_int32_t ;
struct TYPE_3__ {char* label; int /*<<< orphan*/  rpool; int /*<<< orphan*/  u_states_tot; scalar_t__* bytes; scalar_t__* packets; scalar_t__ evaluations; void* action; } ;
struct pfioc_rule {scalar_t__ nr; char* anchor_call; TYPE_1__ rule; int /*<<< orphan*/  ticket; int /*<<< orphan*/  action; int /*<<< orphan*/  anchor; } ;
typedef  int /*<<< orphan*/  pr ;
typedef  enum pfctl_show { ____Placeholder_pfctl_show } pfctl_show ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETRULE ; 
 int /*<<< orphan*/  DIOCGETRULES ; 
 int /*<<< orphan*/  INDENT (int,int) ; 
 scalar_t__ MAXPATHLEN ; 
#define  PFCTL_SHOW_LABELS 130 
#define  PFCTL_SHOW_NOTHING 129 
#define  PFCTL_SHOW_RULES 128 
 int /*<<< orphan*/  PF_GET_CLR_CNTR ; 
 int PF_OPT_CLRRULECTRS ; 
 int PF_OPT_DEBUG ; 
 int PF_OPT_NUMERIC ; 
 int PF_OPT_RECURSE ; 
 int PF_OPT_SHOWALL ; 
 int PF_OPT_VERBOSE ; 
 int PF_OPT_VERBOSE2 ; 
 void* PF_PASS ; 
 void* PF_SCRUB ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_rule*) ; 
 int labels ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct pfioc_rule*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfctl_clear_pool (int /*<<< orphan*/ *) ; 
 scalar_t__ pfctl_get_pool (int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,void*,char*) ; 
 int /*<<< orphan*/  pfctl_print_rule_counters (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pfctl_print_title (char*) ; 
 int /*<<< orphan*/  print_rule (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
pfctl_show_rules(int dev, char *path, int opts, enum pfctl_show format,
    char *anchorname, int depth)
{
	struct pfioc_rule pr;
	u_int32_t nr, mnr, header = 0;
	int rule_numbers = opts & (PF_OPT_VERBOSE2 | PF_OPT_DEBUG);
	int numeric = opts & PF_OPT_NUMERIC;
	int len = strlen(path);
	int brace;
	char *p;

	if (path[0])
		snprintf(&path[len], MAXPATHLEN - len, "/%s", anchorname);
	else
		snprintf(&path[len], MAXPATHLEN - len, "%s", anchorname);

	memset(&pr, 0, sizeof(pr));
	memcpy(pr.anchor, path, sizeof(pr.anchor));
	if (opts & PF_OPT_SHOWALL) {
		pr.rule.action = PF_PASS;
		if (ioctl(dev, DIOCGETRULES, &pr)) {
			warn("DIOCGETRULES");
			goto error;
		}
		header++;
	}
	pr.rule.action = PF_SCRUB;
	if (ioctl(dev, DIOCGETRULES, &pr)) {
		warn("DIOCGETRULES");
		goto error;
	}
	if (opts & PF_OPT_SHOWALL) {
		if (format == PFCTL_SHOW_RULES && (pr.nr > 0 || header))
			pfctl_print_title("FILTER RULES:");
		else if (format == PFCTL_SHOW_LABELS && labels)
			pfctl_print_title("LABEL COUNTERS:");
	}
	mnr = pr.nr;
	if (opts & PF_OPT_CLRRULECTRS)
		pr.action = PF_GET_CLR_CNTR;

	for (nr = 0; nr < mnr; ++nr) {
		pr.nr = nr;
		if (ioctl(dev, DIOCGETRULE, &pr)) {
			warn("DIOCGETRULE");
			goto error;
		}

		if (pfctl_get_pool(dev, &pr.rule.rpool,
		    nr, pr.ticket, PF_SCRUB, path) != 0)
			goto error;

		switch (format) {
		case PFCTL_SHOW_LABELS:
			break;
		case PFCTL_SHOW_RULES:
			if (pr.rule.label[0] && (opts & PF_OPT_SHOWALL))
				labels = 1;
			print_rule(&pr.rule, pr.anchor_call, rule_numbers, numeric);
			printf("\n");
			pfctl_print_rule_counters(&pr.rule, opts);
			break;
		case PFCTL_SHOW_NOTHING:
			break;
		}
		pfctl_clear_pool(&pr.rule.rpool);
	}
	pr.rule.action = PF_PASS;
	if (ioctl(dev, DIOCGETRULES, &pr)) {
		warn("DIOCGETRULES");
		goto error;
	}
	mnr = pr.nr;
	for (nr = 0; nr < mnr; ++nr) {
		pr.nr = nr;
		if (ioctl(dev, DIOCGETRULE, &pr)) {
			warn("DIOCGETRULE");
			goto error;
		}

		if (pfctl_get_pool(dev, &pr.rule.rpool,
		    nr, pr.ticket, PF_PASS, path) != 0)
			goto error;

		switch (format) {
		case PFCTL_SHOW_LABELS:
			if (pr.rule.label[0]) {
				printf("%s %llu %llu %llu %llu"
				    " %llu %llu %llu %ju\n",
				    pr.rule.label,
				    (unsigned long long)pr.rule.evaluations,
				    (unsigned long long)(pr.rule.packets[0] +
				    pr.rule.packets[1]),
				    (unsigned long long)(pr.rule.bytes[0] +
				    pr.rule.bytes[1]),
				    (unsigned long long)pr.rule.packets[0],
				    (unsigned long long)pr.rule.bytes[0],
				    (unsigned long long)pr.rule.packets[1],
				    (unsigned long long)pr.rule.bytes[1],
				    (uintmax_t)pr.rule.u_states_tot);
			}
			break;
		case PFCTL_SHOW_RULES:
			brace = 0;
			if (pr.rule.label[0] && (opts & PF_OPT_SHOWALL))
				labels = 1;
			INDENT(depth, !(opts & PF_OPT_VERBOSE));
			if (pr.anchor_call[0] &&
			   ((((p = strrchr(pr.anchor_call, '_')) != NULL) &&
			   ((void *)p == (void *)pr.anchor_call ||
			   *(--p) == '/')) || (opts & PF_OPT_RECURSE))) {
				brace++;
				if ((p = strrchr(pr.anchor_call, '/')) !=
				    NULL)
					p++;
				else
					p = &pr.anchor_call[0];
			} else
				p = &pr.anchor_call[0];
		
			print_rule(&pr.rule, p, rule_numbers, numeric);
			if (brace)
				printf(" {\n");
			else
				printf("\n");
			pfctl_print_rule_counters(&pr.rule, opts);
			if (brace) { 
				pfctl_show_rules(dev, path, opts, format,
				    p, depth + 1);
				INDENT(depth, !(opts & PF_OPT_VERBOSE));
				printf("}\n");
			}
			break;
		case PFCTL_SHOW_NOTHING:
			break;
		}
		pfctl_clear_pool(&pr.rule.rpool);
	}
	path[len] = '\0';
	return (0);

 error:
	path[len] = '\0';
	return (-1);
}