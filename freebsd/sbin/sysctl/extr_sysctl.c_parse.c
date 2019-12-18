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
typedef  int u_int ;
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int BUFSIZ ; 
 size_t Bflag ; 
 int CTLFLAG_TUN ; 
 int CTLFLAG_WR ; 
 int CTLTYPE ; 
#define  CTLTYPE_INT 143 
#define  CTLTYPE_LONG 142 
 int CTLTYPE_NODE ; 
#define  CTLTYPE_S16 141 
#define  CTLTYPE_S32 140 
#define  CTLTYPE_S64 139 
#define  CTLTYPE_S8 138 
#define  CTLTYPE_STRING 137 
#define  CTLTYPE_U16 136 
#define  CTLTYPE_U32 135 
#define  CTLTYPE_U64 134 
#define  CTLTYPE_U8 133 
#define  CTLTYPE_UINT 132 
#define  CTLTYPE_ULONG 131 
 int CTL_MAXNAME ; 
 int ENOENT ; 
#define  ENOMEM 130 
#define  ENOTDIR 129 
#define  EOPNOTSUPP 128 
 scalar_t__ Tflag ; 
 scalar_t__ Wflag ; 
 int /*<<< orphan*/  bflag ; 
 int /*<<< orphan*/ * ctl_typename ; 
 scalar_t__ dflag ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ iflag ; 
 scalar_t__ isspace (int) ; 
 int name2oid (char*,int*) ; 
 int nflag ; 
 scalar_t__ oidfmt (int*,int,char*,int*) ; 
 int /*<<< orphan*/  parse_numeric (char*,char*,int,void**,size_t*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ qflag ; 
 int show_var (int*,int) ; 
 int snprintf (char*,int,char*,...) ; 
 size_t strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int sysctl (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  sysctl_all (int*,int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char const*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
parse(const char *string, int lineno)
{
	int len, i, j;
	const void *newval;
	char *newvalstr = NULL;
	void *newbuf;
	size_t newsize = Bflag;
	int mib[CTL_MAXNAME];
	char *cp, *bufp, buf[BUFSIZ], fmt[BUFSIZ], line[BUFSIZ];
	u_int kind;

	if (lineno)
		snprintf(line, sizeof(line), " at line %d", lineno);
	else
		line[0] = '\0';

	cp = buf;
	if (snprintf(buf, BUFSIZ, "%s", string) >= BUFSIZ) {
		warnx("oid too long: '%s'%s", string, line);
		return (1);
	}
	bufp = strsep(&cp, "=:");
	if (cp != NULL) {
		/* Tflag just lists tunables, do not allow assignment */
		if (Tflag || Wflag) {
			warnx("Can't set variables when using -T or -W");
			usage();
		}
		while (isspace(*cp))
			cp++;
		/* Strip a pair of " or ' if any. */
		switch (*cp) {
		case '\"':
		case '\'':
			if (cp[strlen(cp) - 1] == *cp)
				cp[strlen(cp) - 1] = '\0';
			cp++;
		}
		newvalstr = cp;
		newsize = strlen(cp);
	}
	/* Trim spaces */
	cp = bufp + strlen(bufp) - 1;
	while (cp >= bufp && isspace((int)*cp)) {
		*cp = '\0';
		cp--;
	}
	len = name2oid(bufp, mib);

	if (len < 0) {
		if (iflag)
			return (0);
		if (qflag)
			return (1);
		else {
			if (errno == ENOENT) {
				warnx("unknown oid '%s'%s", bufp, line);
			} else {
				warn("unknown oid '%s'%s", bufp, line);
			}
			return (1);
		}
	}

	if (oidfmt(mib, len, fmt, &kind)) {
		warn("couldn't find format of oid '%s'%s", bufp, line);
		if (iflag)
			return (1);
		else
			exit(1);
	}

	if (newvalstr == NULL || dflag) {
		if ((kind & CTLTYPE) == CTLTYPE_NODE) {
			if (dflag) {
				i = show_var(mib, len);
				if (!i && !bflag)
					putchar('\n');
			}
			sysctl_all(mib, len);
		} else {
			i = show_var(mib, len);
			if (!i && !bflag)
				putchar('\n');
		}
	} else {
		if ((kind & CTLTYPE) == CTLTYPE_NODE) {
			warnx("oid '%s' isn't a leaf node%s", bufp, line);
			return (1);
		}

		if (!(kind & CTLFLAG_WR)) {
			if (kind & CTLFLAG_TUN) {
				warnx("oid '%s' is a read only tunable%s", bufp, line);
				warnx("Tunable values are set in /boot/loader.conf");
			} else
				warnx("oid '%s' is read only%s", bufp, line);
			return (1);
		}

		switch (kind & CTLTYPE) {
		case CTLTYPE_INT:
		case CTLTYPE_UINT:
		case CTLTYPE_LONG:
		case CTLTYPE_ULONG:
		case CTLTYPE_S8:
		case CTLTYPE_S16:
		case CTLTYPE_S32:
		case CTLTYPE_S64:
		case CTLTYPE_U8:
		case CTLTYPE_U16:
		case CTLTYPE_U32:
		case CTLTYPE_U64:
			if (strlen(newvalstr) == 0) {
				warnx("empty numeric value");
				return (1);
			}
			/* FALLTHROUGH */
		case CTLTYPE_STRING:
			break;
		default:
			warnx("oid '%s' is type %d,"
				" cannot set that%s", bufp,
				kind & CTLTYPE, line);
			return (1);
		}

		newbuf = NULL;

		switch (kind & CTLTYPE) {
		case CTLTYPE_STRING:
			newval = newvalstr;
			break;
		default:
			newsize = 0;
			while ((cp = strsep(&newvalstr, " ,")) != NULL) {
				if (*cp == '\0')
					continue;
				if (!parse_numeric(cp, fmt, kind, &newbuf,
				    &newsize)) {
					warnx("invalid %s '%s'%s",
					    ctl_typename[kind & CTLTYPE],
					    cp, line);
					free(newbuf);
					return (1);
				}
			}
			newval = newbuf;
			break;
		}

		i = show_var(mib, len);
		if (sysctl(mib, len, 0, 0, newval, newsize) == -1) {
			free(newbuf);
			if (!i && !bflag)
				putchar('\n');
			switch (errno) {
			case EOPNOTSUPP:
				warnx("%s: value is not available%s",
					string, line);
				return (1);
			case ENOTDIR:
				warnx("%s: specification is incomplete%s",
					string, line);
				return (1);
			case ENOMEM:
				warnx("%s: type is unknown to this program%s",
					string, line);
				return (1);
			default:
				warn("%s%s", string, line);
				return (1);
			}
		}
		free(newbuf);
		if (!bflag)
			printf(" -> ");
		i = nflag;
		nflag = 1;
		j = show_var(mib, len);
		if (!j && !bflag)
			putchar('\n');
		nflag = i;
	}

	return (0);
}