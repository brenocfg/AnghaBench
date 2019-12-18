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
struct passwd {int /*<<< orphan*/  pw_passwd; } ;
typedef  int /*<<< orphan*/  newline ;

/* Variables and functions */
 int HEXKEYBYTES ; 
 int KEYCHECKSUMSIZE ; 
 int /*<<< orphan*/  MAXNETNAMELEN ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  PKMAP ; 
 int /*<<< orphan*/  ROOTKEY ; 
 int /*<<< orphan*/  close (int) ; 
 char* crypt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  domain ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genkeys (char*,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 char* getpass (char*) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 scalar_t__ getuid () ; 
 scalar_t__ host2netname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ key_setsecret (char*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int setpublicmap (char*,char*,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ user2netname (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,char*,int) ; 
 int /*<<< orphan*/  xdecrypt (char*,char*) ; 
 int /*<<< orphan*/  xencrypt (char*,char*) ; 
 int /*<<< orphan*/  yp_get_default_domain (int /*<<< orphan*/ *) ; 
 scalar_t__ yp_master (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  yperr_string (int) ; 
 struct passwd* ypgetpwuid (scalar_t__) ; 

int
main(int argc, char **argv)
{
	char name[MAXNETNAMELEN+1];
	char public[HEXKEYBYTES + 1];
	char secret[HEXKEYBYTES + 1];
	char crypt1[HEXKEYBYTES + KEYCHECKSUMSIZE + 1];
	char crypt2[HEXKEYBYTES + KEYCHECKSUMSIZE + 1];
	int status;	
	char *pass;
	struct passwd *pw;
	uid_t uid;
	int force = 0;
	int ch;
#ifdef YP
	char *master;
#endif
#ifdef YPPASSWD
	char *cryptpw;
#endif

	while ((ch = getopt(argc, argv, "f")) != -1)
		switch(ch) {
		case 'f':
			force = 1;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 0)
		usage();

#ifdef YP
	(void)yp_get_default_domain(&domain);
	if (yp_master(domain, PKMAP, &master) != 0)
		errx(1, "can't find master of publickey database");
#endif
	uid = getuid() /*geteuid()*/;
	if (uid == 0) {
		if (host2netname(name, NULL, NULL) == 0)
			errx(1, "cannot convert hostname to netname");
	} else {
		if (user2netname(name, uid, NULL) == 0)
			errx(1, "cannot convert username to netname");
	}
	(void)printf("Generating new key for %s.\n", name);

	if (!force) {
		if (uid != 0) {
#ifdef YPPASSWD
			pw = ypgetpwuid(uid);
#else
			pw = getpwuid(uid);
#endif
			if (pw == NULL) {
#ifdef YPPASSWD
				errx(1,
			"no NIS password entry found: can't change key");
#else
				errx(1,
			"no password entry found: can't change key");
#endif
			}
		} else {
			pw = getpwuid(0);
			if (pw == NULL)
			  errx(1, "no password entry found: can't change key");
		}
	}
	pass = getpass("Password:");
#ifdef YPPASSWD
	if (!force) {
		cryptpw = crypt(pass, pw->pw_passwd);
		if (cryptpw == NULL || strcmp(cryptpw, pw->pw_passwd) != 0)
			errx(1, "invalid password");
	}
#else
	force = 1;	/* Make this mandatory */
#endif
	genkeys(public, secret, pass);	

	memcpy(crypt1, secret, HEXKEYBYTES);
	memcpy(crypt1 + HEXKEYBYTES, secret, KEYCHECKSUMSIZE);
	crypt1[HEXKEYBYTES + KEYCHECKSUMSIZE] = 0;
	xencrypt(crypt1, pass);

	if (force) {
		memcpy(crypt2, crypt1, HEXKEYBYTES + KEYCHECKSUMSIZE + 1);	
		xdecrypt(crypt2, getpass("Retype password:"));
		if (memcmp(crypt2, crypt2 + HEXKEYBYTES, KEYCHECKSUMSIZE) != 0
			|| memcmp(crypt2, secret, HEXKEYBYTES) != 0)
			errx(1, "password incorrect");
	}

#ifdef YP
	(void)printf("Sending key change request to %s...\n", master);
#endif
	status = setpublicmap(name, public, crypt1);
	if (status != 0) {
#ifdef YP
		errx(1, "unable to update NIS database (%u): %s",
				status, yperr_string(status));
#else
		errx(1, "unable to update publickey database");
#endif
	}

	if (uid == 0) {
		/*
		 * Root users store their key in /etc/$ROOTKEY so
		 * that they can auto reboot without having to be
		 * around to type a password. Storing this in a file
		 * is rather dubious: it should really be in the EEPROM
		 * so it does not go over the net.
		 */
		int fd;

		fd = open(ROOTKEY, O_WRONLY|O_TRUNC|O_CREAT, 0);
		if (fd < 0) {
			warn("%s", ROOTKEY);
		} else {
			char newline = '\n';

			if (write(fd, secret, strlen(secret)) < 0 ||
			    write(fd, &newline, sizeof(newline)) < 0)
				warn("%s: write", ROOTKEY);
		}
		close(fd);
	}

	if (key_setsecret(secret) < 0)
		errx(1, "unable to login with new secret key");
	(void)printf("Done.\n");
	exit(0);
	/* NOTREACHED */
}