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
typedef  int /*<<< orphan*/  tmpbuf ;
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int BUFSIZE ; 
 int RPP_ECHO_OFF ; 
 int RPP_REQUIRE_TTY ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  explicit_bzero (char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,int /*<<< orphan*/ ) ; 
 char* readpassphrase (char*,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
eli_genkey_passphrase_prompt(struct gctl_req *req, bool new, char *passbuf,
    size_t passbufsize)
{
	char *p;

	for (;;) {
		p = readpassphrase(
		    new ? "Enter new passphrase: " : "Enter passphrase: ",
		    passbuf, passbufsize, RPP_ECHO_OFF | RPP_REQUIRE_TTY);
		if (p == NULL) {
			explicit_bzero(passbuf, passbufsize);
			gctl_error(req, "Cannot read passphrase: %s.",
			    strerror(errno));
			return (-1);
		}

		if (new) {
			char tmpbuf[BUFSIZE];

			p = readpassphrase("Reenter new passphrase: ",
			    tmpbuf, sizeof(tmpbuf),
			    RPP_ECHO_OFF | RPP_REQUIRE_TTY);
			if (p == NULL) {
				explicit_bzero(passbuf, passbufsize);
				gctl_error(req,
				    "Cannot read passphrase: %s.",
				    strerror(errno));
				return (-1);
			}

			if (strcmp(passbuf, tmpbuf) != 0) {
				explicit_bzero(passbuf, passbufsize);
				fprintf(stderr, "They didn't match.\n");
				continue;
			}
			explicit_bzero(tmpbuf, sizeof(tmpbuf));
		}
		return (0);
	}
	/* NOTREACHED */
}