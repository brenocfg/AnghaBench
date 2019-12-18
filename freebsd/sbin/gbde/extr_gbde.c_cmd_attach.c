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
typedef  char const u_char ;
struct gctl_req {int dummy; } ;
struct g_bde_softc {char const* sha2; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int SHA512_DIGEST_LENGTH ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,char const*) ; 
 int open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int,char const*,int) ; 

__attribute__((used)) static void
cmd_attach(const struct g_bde_softc *sc, const char *dest, const char *lfile)
{
	int ffd;
	u_char buf[16];
	struct gctl_req *r;
	const char *errstr;

	r = gctl_get_handle();
	gctl_ro_param(r, "verb", -1, "create geom");
	gctl_ro_param(r, "class", -1, "BDE");
	gctl_ro_param(r, "provider", -1, dest);
	gctl_ro_param(r, "pass", SHA512_DIGEST_LENGTH, sc->sha2);
	if (lfile != NULL) {
		ffd = open(lfile, O_RDONLY, 0);
		if (ffd < 0)
			err(1, "%s", lfile);
		read(ffd, buf, 16);
		gctl_ro_param(r, "key", 16, buf);
		close(ffd);
	}
	errstr = gctl_issue(r);
	if (errstr != NULL)
		errx(1, "Attach to %s failed: %s", dest, errstr);

	exit (0);
}