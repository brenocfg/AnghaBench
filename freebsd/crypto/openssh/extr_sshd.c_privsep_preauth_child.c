#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  scalar_t__ gid_t ;
struct TYPE_5__ {scalar_t__ gss_authentication; } ;
struct TYPE_4__ {scalar_t__ pw_gid; scalar_t__ pw_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  _PATH_PRIVSEP_CHROOT_DIR ; 
 int chdir (char*) ; 
 int chroot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug3 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demote_sensitive_data () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_3__ options ; 
 int /*<<< orphan*/  permanently_set_uid (TYPE_1__*) ; 
 int /*<<< orphan*/  privsep_challenge_enable () ; 
 scalar_t__ privsep_chroot ; 
 TYPE_1__* privsep_pw ; 
 int /*<<< orphan*/  reseed_prngs () ; 
 scalar_t__ setgroups (int,scalar_t__*) ; 
 int /*<<< orphan*/  ssh_gssapi_prepare_supported_oids () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
privsep_preauth_child(void)
{
	gid_t gidset[1];

	/* Enable challenge-response authentication for privilege separation */
	privsep_challenge_enable();

#ifdef GSSAPI
	/* Cache supported mechanism OIDs for later use */
	if (options.gss_authentication)
		ssh_gssapi_prepare_supported_oids();
#endif

	reseed_prngs();

	/* Demote the private keys to public keys. */
	demote_sensitive_data();

	/* Demote the child */
	if (privsep_chroot) {
		/* Change our root directory */
		if (chroot(_PATH_PRIVSEP_CHROOT_DIR) == -1)
			fatal("chroot(\"%s\"): %s", _PATH_PRIVSEP_CHROOT_DIR,
			    strerror(errno));
		if (chdir("/") == -1)
			fatal("chdir(\"/\"): %s", strerror(errno));

		/* Drop our privileges */
		debug3("privsep user:group %u:%u", (u_int)privsep_pw->pw_uid,
		    (u_int)privsep_pw->pw_gid);
		gidset[0] = privsep_pw->pw_gid;
		if (setgroups(1, gidset) < 0)
			fatal("setgroups: %.100s", strerror(errno));
		permanently_set_uid(privsep_pw);
	}
}