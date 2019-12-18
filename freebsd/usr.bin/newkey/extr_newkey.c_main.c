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
struct passwd {scalar_t__ pw_uid; } ;
struct hostent {char* h_name; } ;

/* Variables and functions */
 int HEXKEYBYTES ; 
 int KEYCHECKSUMSIZE ; 
 int /*<<< orphan*/  MAXNETNAMELEN ; 
 int /*<<< orphan*/  YPDBPATH ; 
 scalar_t__ chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_string (int) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genkeys (char*,char*,char*) ; 
 scalar_t__ geteuid () ; 
 struct hostent* gethostbyname (char*) ; 
 char* getpass (char*) ; 
 struct passwd* getpwnam (char*) ; 
 int /*<<< orphan*/  host2netname (char*,char*,char*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int setpublicmap (char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  user2netname (char*,int,char*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdecrypt (char*,char*) ; 
 int /*<<< orphan*/  xencrypt (char*,char*) ; 
 int /*<<< orphan*/  yperr_string (int) ; 

int
main(int argc, char *argv[])
{
	char name[MAXNETNAMELEN + 1];
	char public[HEXKEYBYTES + 1];
	char secret[HEXKEYBYTES + 1];
	char crypt1[HEXKEYBYTES + KEYCHECKSUMSIZE + 1];
	char crypt2[HEXKEYBYTES + KEYCHECKSUMSIZE + 1];
	int status;	
	char *pass;
	struct passwd *pw;
#ifdef undef
	struct hostent *h;
#endif

	if (argc != 3 || !(strcmp(argv[1], "-u") == 0 ||
		strcmp(argv[1], "-h") == 0)) {
		usage();
	}
	if (geteuid() != 0)
		errx(1, "must be superuser");

#ifdef YP
	if (chdir(YPDBPATH) < 0)
		warn("cannot chdir to %s", YPDBPATH);
#endif	/* YP */
	if (strcmp(argv[1], "-u") == 0) {
		pw = getpwnam(argv[2]);
		if (pw == NULL)
			errx(1, "unknown user: %s", argv[2]);
		(void)user2netname(name, (int)pw->pw_uid, (char *)NULL);
	} else {
#ifdef undef
		h = gethostbyname(argv[2]);
		if (h == NULL)
			errx(1, "unknown host: %s", argv[1]);
		(void)host2netname(name, h->h_name, (char *)NULL);
#else
		(void)host2netname(name, argv[2], (char *)NULL);
#endif
	}

	(void)printf("Adding new key for %s.\n", name);
	pass = getpass("New password:");
	genkeys(public, secret, pass);

	memcpy(crypt1, secret, HEXKEYBYTES);
	memcpy(crypt1 + HEXKEYBYTES, secret, KEYCHECKSUMSIZE);
	crypt1[HEXKEYBYTES + KEYCHECKSUMSIZE] = 0;
	xencrypt(crypt1, pass);

	memcpy(crypt2, crypt1, HEXKEYBYTES + KEYCHECKSUMSIZE + 1);	
	xdecrypt(crypt2, getpass("Retype password:"));
	if (memcmp(crypt2, crypt2 + HEXKEYBYTES, KEYCHECKSUMSIZE) != 0 ||
		memcmp(crypt2, secret, HEXKEYBYTES) != 0)
		errx(1, "password incorrect");

#ifdef YP
	(void)printf("Please wait for the database to get updated...\n");
#endif
	if ((status = setpublicmap(name, public, crypt1))) {
#ifdef YP
		errx(1, "unable to update NIS database (%u): %s", 
			status, yperr_string(status));
#else
		errx(1, "unable to update publickey database (%u): %s",
			status, err_string(status));
#endif
	}
	(void)printf("Your new key has been successfully stored away.\n");
	exit(0);
	/* NOTREACHED */
}