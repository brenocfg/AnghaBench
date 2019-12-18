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
struct userconf {char* nispasswd; char* dotdir; char* newmail; char* logfile; char* home; char* shelldir; char* shell_default; char* default_group; char* default_class; void* password_days; void* expire_days; void* max_gid; void* min_gid; void* max_uid; void* min_uid; int /*<<< orphan*/ * groups; int /*<<< orphan*/  homemode; void* reuse_gids; void* reuse_uids; int /*<<< orphan*/  default_password; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  char mode_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * GETGRNAM (char*) ; 
 int /*<<< orphan*/  GID_MAX ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  UID_MAX ; 
 int /*<<< orphan*/  _DEF_DIRMODE ; 
#define  _UC_DEFAULTCLASS 150 
#define  _UC_DEFAULTGROUP 149 
#define  _UC_DEFAULTPWD 148 
#define  _UC_DEFAULTSHELL 147 
#define  _UC_DOTDIR 146 
#define  _UC_EXPIRE 145 
#define  _UC_EXTRAGROUPS 144 
#define  _UC_FIELDS 143 
#define  _UC_HOMEMODE 142 
#define  _UC_HOMEROOT 141 
#define  _UC_LOGFILE 140 
#define  _UC_MAXGID 139 
 int _UC_MAXSHELLS ; 
#define  _UC_MAXUID 138 
#define  _UC_MINGID 137 
#define  _UC_MINUID 136 
#define  _UC_NEWMAIL 135 
#define  _UC_NISPASSWD 134 
#define  _UC_NONE 133 
#define  _UC_PASSWORD 132 
#define  _UC_REUSEGID 131 
#define  _UC_REUSEUID 130 
#define  _UC_SHELLPATH 129 
#define  _UC_SHELLS 128 
 void* boolean_val (char*,int) ; 
 scalar_t__ bourne_shell ; 
 struct userconf config ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getmode (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kwds ; 
 char* newstr (char*) ; 
 int /*<<< orphan*/  passwd_val (char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* setmode (char*) ; 
 int /*<<< orphan*/  sl_add (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * sl_init () ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strtok (char*,char const*) ; 
 void* strtonum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 void* strtounum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 char** system_shells ; 
 char* unquote (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

struct userconf *
read_userconfig(char const * file)
{
	FILE	*fp;
	char	*buf, *p;
	const char *errstr;
	size_t	linecap;
	ssize_t	linelen;

	buf = NULL;
	linecap = 0;

	if ((fp = fopen(file, "r")) == NULL)
		return (&config);

	while ((linelen = getline(&buf, &linecap, fp)) > 0) {
		if (*buf && (p = strtok(buf, " \t\r\n=")) != NULL && *p != '#') {
			static char const toks[] = " \t\r\n,=";
			char           *q = strtok(NULL, toks);
			int             i = 0;
			mode_t          *modeset;

			while (i < _UC_FIELDS && strcmp(p, kwds[i]) != 0)
				++i;
#if debugging
			if (i == _UC_FIELDS)
				printf("Got unknown kwd `%s' val=`%s'\n", p, q ? q : "");
			else
				printf("Got kwd[%s]=%s\n", p, q);
#endif
			switch (i) {
			case _UC_DEFAULTPWD:
				config.default_password = passwd_val(q, 1);
				break;
			case _UC_REUSEUID:
				config.reuse_uids = boolean_val(q, 0);
				break;
			case _UC_REUSEGID:
				config.reuse_gids = boolean_val(q, 0);
				break;
			case _UC_NISPASSWD:
				config.nispasswd = (q == NULL || !boolean_val(q, 1))
					? NULL : newstr(q);
				break;
			case _UC_DOTDIR:
				config.dotdir = (q == NULL || !boolean_val(q, 1))
					? NULL : newstr(q);
				break;
				case _UC_NEWMAIL:
				config.newmail = (q == NULL || !boolean_val(q, 1))
					? NULL : newstr(q);
				break;
			case _UC_LOGFILE:
				config.logfile = (q == NULL || !boolean_val(q, 1))
					? NULL : newstr(q);
				break;
			case _UC_HOMEROOT:
				config.home = (q == NULL || !boolean_val(q, 1))
					? "/home" : newstr(q);
				break;
			case _UC_HOMEMODE:
				modeset = setmode(q);
				config.homemode = (q == NULL || !boolean_val(q, 1))
					? _DEF_DIRMODE : getmode(modeset, _DEF_DIRMODE);
				free(modeset);
				break;
			case _UC_SHELLPATH:
				config.shelldir = (q == NULL || !boolean_val(q, 1))
					? "/bin" : newstr(q);
				break;
			case _UC_SHELLS:
				for (i = 0; i < _UC_MAXSHELLS && q != NULL; i++, q = strtok(NULL, toks))
					system_shells[i] = newstr(q);
				if (i > 0)
					while (i < _UC_MAXSHELLS)
						system_shells[i++] = NULL;
				break;
			case _UC_DEFAULTSHELL:
				config.shell_default = (q == NULL || !boolean_val(q, 1))
					? (char *) bourne_shell : newstr(q);
				break;
			case _UC_DEFAULTGROUP:
				q = unquote(q);
				config.default_group = (q == NULL || !boolean_val(q, 1) || GETGRNAM(q) == NULL)
					? NULL : newstr(q);
				break;
			case _UC_EXTRAGROUPS:
				while ((q = strtok(NULL, toks)) != NULL) {
					if (config.groups == NULL)
						config.groups = sl_init();
					sl_add(config.groups, newstr(q));
				}
				break;
			case _UC_DEFAULTCLASS:
				config.default_class = (q == NULL || !boolean_val(q, 1))
					? NULL : newstr(q);
				break;
			case _UC_MINUID:
				if ((q = unquote(q)) != NULL) {
					config.min_uid = strtounum(q, 0,
					    UID_MAX, &errstr);
					if (errstr)
						warnx("Invalid min_uid: '%s';"
						    " ignoring", q);
				}
				break;
			case _UC_MAXUID:
				if ((q = unquote(q)) != NULL) {
					config.max_uid = strtounum(q, 0,
					    UID_MAX, &errstr);
					if (errstr)
						warnx("Invalid max_uid: '%s';"
						    " ignoring", q);
				}
				break;
			case _UC_MINGID:
				if ((q = unquote(q)) != NULL) {
					config.min_gid = strtounum(q, 0,
					    GID_MAX, &errstr);
					if (errstr)
						warnx("Invalid min_gid: '%s';"
						    " ignoring", q);
				}
				break;
			case _UC_MAXGID:
				if ((q = unquote(q)) != NULL) {
					config.max_gid = strtounum(q, 0,
					    GID_MAX, &errstr);
					if (errstr)
						warnx("Invalid max_gid: '%s';"
						    " ignoring", q);
				}
				break;
			case _UC_EXPIRE:
				if ((q = unquote(q)) != NULL) {
					config.expire_days = strtonum(q, 0,
					    INT_MAX, &errstr);
					if (errstr)
						warnx("Invalid expire days:"
						    " '%s'; ignoring", q);
				}
				break;
			case _UC_PASSWORD:
				if ((q = unquote(q)) != NULL) {
					config.password_days = strtonum(q, 0,
					    INT_MAX, &errstr);
					if (errstr)
						warnx("Invalid password days:"
						    " '%s'; ignoring", q);
				}
				break;
			case _UC_FIELDS:
			case _UC_NONE:
				break;
			}
		}
	}
	free(buf);
	fclose(fp);

	return (&config);
}