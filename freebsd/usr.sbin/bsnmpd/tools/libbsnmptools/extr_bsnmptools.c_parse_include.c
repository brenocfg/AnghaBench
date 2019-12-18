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
struct snmp_toolinfo {int dummy; } ;
struct asn_oid {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int EOF ; 
#define  INC_CUT 130 
#define  INC_LIST 129 
#define  INC_PATH 128 
 struct asn_oid IsoOrgDod_OID ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int getsubopt1 (char**,char const* const*,char**,char**) ; 
 int /*<<< orphan*/  memset (struct asn_oid*,int /*<<< orphan*/ ,int) ; 
 int parse_flist (struct snmp_toolinfo*,char*,char*,struct asn_oid*) ; 
 int parse_path (char*) ; 
 int /*<<< orphan*/  snmp_parse_numoid (char*,struct asn_oid*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suboptarg ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int32_t
parse_include(struct snmp_toolinfo *snmptoolctx, char *opt_arg)
{
	char path[MAXPATHLEN + 1];
	int32_t cut_dflt, len, subopt;
	struct asn_oid cut;
	char *val, *option;
	const char *const subopts[] = {
		"cut",
		"path",
		"file",
		NULL
	};

#define	INC_CUT		0
#define	INC_PATH	1
#define	INC_LIST	2

	assert(opt_arg != NULL);

	/* if (opt == 'i')
		free_filelist(snmptoolctx, ); */
	/*
	 * This function should be called only after getopt(3) - otherwise if
	 * no previous validation of opt_arg strlen() may not return what is
	 * expected.
	 */

	path[0] = '\0';
	memset(&cut, 0, sizeof(struct asn_oid));
	cut_dflt = -1;

	while ((subopt = getsubopt1(&opt_arg, subopts, &val, &option)) != EOF) {
		switch (subopt) {
		    case INC_CUT:
			if (val == NULL) {
				warnx("Suboption 'cut' requires an argument");
				return (-1);
			} else {
				if (snmp_parse_numoid(val, &cut) < 0)
					return (-1);
			}
			cut_dflt = 1;
			break;

		    case INC_PATH:
			if ((len = parse_path(val)) < 0)
				return (-1);
			strlcpy(path, val, len + 1);
			break;

		    case INC_LIST:
			if (val == NULL)
				return (-1);
			if (cut_dflt == -1)
				len = parse_flist(snmptoolctx, val, path, &IsoOrgDod_OID);
			else
				len = parse_flist(snmptoolctx, val, path, &cut);
			if (len < 0)
				return (-1);
			break;

		    default:
			warnx("Unknown suboption - '%s'", suboptarg);
			return (-1);
		}
	}

	/* XXX: Fix me - returning two is wrong here */
	return (2);
}