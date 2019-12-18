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
typedef  scalar_t__ uid_t ;
struct ypclnt {int /*<<< orphan*/  error; } ;
struct passwd {scalar_t__ pw_uid; int pw_fields; char* pw_passwd; int /*<<< orphan*/  pw_name; } ;
typedef  int /*<<< orphan*/  ENTRY ;

/* Variables and functions */
#define  _PWF_FILES 129 
#define  _PWF_NIS 128 
 int _PWF_SOURCE ; 
 int _PWSCAN_MASTER ; 
 int _PWSCAN_WARN ; 
 int /*<<< orphan*/  __pw_scan (char*,struct passwd*,int) ; 
 int /*<<< orphan*/  baduser () ; 
 char* crypt (char const*,char*) ; 
 struct passwd* edit (int /*<<< orphan*/ ,struct passwd*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (struct passwd*) ; 
 int getopt (int,char**,char*) ; 
 char* getpass (char*) ; 
 struct passwd* getpwnam (char*) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 scalar_t__ getuid () ; 
 int master_mode ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int p_expire (char*,struct passwd*,int /*<<< orphan*/ *) ; 
 int p_shell (char*,struct passwd*,int /*<<< orphan*/ *) ; 
 int pw_copy (int,int,struct passwd*,struct passwd*) ; 
 struct passwd* pw_dup (struct passwd*) ; 
 scalar_t__ pw_equal (struct passwd*,struct passwd*) ; 
 int /*<<< orphan*/  pw_fini () ; 
 scalar_t__ pw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pw_lock () ; 
 int pw_mkdb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pw_tempname () ; 
 int pw_tmp (int) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 int ypclnt_connect (struct ypclnt*) ; 
 int /*<<< orphan*/  ypclnt_free (struct ypclnt*) ; 
 int ypclnt_havepasswdd (struct ypclnt*) ; 
 struct ypclnt* ypclnt_new (char const*,char*,char const*) ; 
 int ypclnt_passwd (struct ypclnt*,struct passwd*,char const*) ; 

int
main(int argc, char *argv[])
{
	enum { NEWSH, LOADENTRY, EDITENTRY, NEWPW, NEWEXP } op;
	struct passwd lpw, *old_pw, *pw;
	int ch, pfd, tfd;
	const char *password;
	char *arg = NULL, *cryptpw;
	uid_t uid;
#ifdef YP
	struct ypclnt *ypclnt;
	const char *yp_domain = NULL, *yp_host = NULL;
#endif

	pw = old_pw = NULL;
	op = EDITENTRY;
#ifdef YP
	while ((ch = getopt(argc, argv, "a:p:s:e:d:h:loy")) != -1)
#else
	while ((ch = getopt(argc, argv, "a:p:s:e:")) != -1)
#endif
		switch (ch) {
		case 'a':
			op = LOADENTRY;
			arg = optarg;
			break;
		case 's':
			op = NEWSH;
			arg = optarg;
			break;
		case 'p':
			op = NEWPW;
			arg = optarg;
			break;
		case 'e':
			op = NEWEXP;
			arg = optarg;
			break;
#ifdef YP
		case 'd':
			yp_domain = optarg;
			break;
		case 'h':
			yp_host = optarg;
			break;
		case 'l':
		case 'o':
		case 'y':
			/* compatibility */
			break;
#endif
		case '?':
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (argc > 1)
		usage();

	uid = getuid();

	if (op == EDITENTRY || op == NEWSH || op == NEWPW || op == NEWEXP) {
		if (argc == 0) {
			if ((pw = getpwuid(uid)) == NULL)
				errx(1, "unknown user: uid %lu",
				    (unsigned long)uid);
		} else {
			if ((pw = getpwnam(*argv)) == NULL)
				errx(1, "unknown user: %s", *argv);
			if (uid != 0 && uid != pw->pw_uid)
				baduser();
		}

		/* Make a copy for later verification */
		if ((pw = pw_dup(pw)) == NULL ||
		    (old_pw = pw_dup(pw)) == NULL)
			err(1, "pw_dup");
	}

#ifdef YP
	if (pw != NULL && (pw->pw_fields & _PWF_SOURCE) == _PWF_NIS) {
		ypclnt = ypclnt_new(yp_domain, "passwd.byname", yp_host);
		master_mode = (ypclnt != NULL &&
		    ypclnt_connect(ypclnt) != -1 &&
		    ypclnt_havepasswdd(ypclnt) == 1);
		ypclnt_free(ypclnt);
	} else
#endif
	master_mode = (uid == 0);

	if (op == NEWSH) {
		/* protect p_shell -- it thinks NULL is /bin/sh */
		if (!arg[0])
			usage();
		if (p_shell(arg, pw, (ENTRY *)NULL) == -1)
			exit(1);
	}

	if (op == NEWEXP) {
		if (uid)	/* only root can change expire */
			baduser();
		if (p_expire(arg, pw, (ENTRY *)NULL) == -1)
			exit(1);
	}

	if (op == LOADENTRY) {
		if (uid)
			baduser();
		pw = &lpw;
		old_pw = NULL;
		if (!__pw_scan(arg, pw, _PWSCAN_WARN|_PWSCAN_MASTER))
			exit(1);
	}

	if (op == NEWPW) {
		if (uid)
			baduser();

		if (strchr(arg, ':'))
			errx(1, "invalid format for password");
		pw->pw_passwd = arg;
	}

	if (op == EDITENTRY) {
		/*
		 * We don't really need pw_*() here, but pw_edit() (used
		 * by edit()) is just too useful...
		 */
		if (pw_init(NULL, NULL))
			err(1, "pw_init()");
		if ((tfd = pw_tmp(-1)) == -1) {
			pw_fini();
			err(1, "pw_tmp()");
		}
		free(pw);
		pw = edit(pw_tempname(), old_pw);
		pw_fini();
		if (pw == NULL)
			err(1, "edit()");
		/* 
		 * pw_equal does not check for crypted passwords, so we
		 * should do it explicitly
		 */
		if (pw_equal(old_pw, pw) && 
		    strcmp(old_pw->pw_passwd, pw->pw_passwd) == 0)
			errx(0, "user information unchanged");
	}

	if (old_pw && !master_mode) {
		password = getpass("Password: ");
		cryptpw = crypt(password, old_pw->pw_passwd);
		if (cryptpw == NULL || strcmp(cryptpw, old_pw->pw_passwd) != 0)
			baduser();
	} else {
		password = "";
	}

	if (old_pw != NULL)
		pw->pw_fields |= (old_pw->pw_fields & _PWF_SOURCE);
	switch (pw->pw_fields & _PWF_SOURCE) {
#ifdef YP
	case _PWF_NIS:
		ypclnt = ypclnt_new(yp_domain, "passwd.byname", yp_host);
		if (ypclnt == NULL) {
			warnx("ypclnt_new failed");
			exit(1);
		}
		if (ypclnt_connect(ypclnt) == -1 ||
		    ypclnt_passwd(ypclnt, pw, password) == -1) {
			warnx("%s", ypclnt->error);
			ypclnt_free(ypclnt);
			exit(1);
		}
		ypclnt_free(ypclnt);
		errx(0, "NIS user information updated");
#endif /* YP */
	case 0:
	case _PWF_FILES:
		if (pw_init(NULL, NULL))
			err(1, "pw_init()");
		if ((pfd = pw_lock()) == -1) {
			pw_fini();
			err(1, "pw_lock()");
		}
		if ((tfd = pw_tmp(-1)) == -1) {
			pw_fini();
			err(1, "pw_tmp()");
		}
		if (pw_copy(pfd, tfd, pw, old_pw) == -1) {
			pw_fini();
			err(1, "pw_copy");
		}
		if (pw_mkdb(pw->pw_name) == -1) {
			pw_fini();
			err(1, "pw_mkdb()");
		}
		pw_fini();
		errx(0, "user information updated");
		break;
	default:
		errx(1, "unsupported passwd source");
	}
}