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
struct sockaddr {int dummy; } ;
struct sadb_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ addr ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (struct sadb_msg*) ; 
 scalar_t__ getuid () ; 
 int ipsec_get_policylen (char*) ; 
 char* ipsec_set_policy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_strerror () ; 
 int pfkey_open () ; 
 struct sadb_msg* pfkey_recv (int) ; 
 scalar_t__ pfkey_send_spdadd (int,struct sockaddr*,int,struct sockaddr*,int,int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pfkey_send_spdadd2 (int,struct sockaddr*,int,struct sockaddr*,int,int,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pfkey_send_spddelete (int,struct sockaddr*,int,struct sockaddr*,int,int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pfkey_send_spddelete2 (int,int) ; 
 scalar_t__ pfkey_send_spdflush (int) ; 
 scalar_t__ pfkey_send_spdget (int,int) ; 
 scalar_t__ pfkey_send_spdsetidx (int,struct sockaddr*,int,struct sockaddr*,int,int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pfkey_send_spdupdate (int,struct sockaddr*,int,struct sockaddr*,int,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int test2sub (int) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
test2()
{
	int so;
	char *pol1 = "out ipsec";
	char *pol2 = "out ipsec ah/transport//use";
	char *sp1, *sp2;
	int splen1, splen2;
	int spid;
	struct sadb_msg *m;

	printf("TEST2\n");
	if (getuid() != 0)
		errx(1, "root privilege required.");

	sp1 = ipsec_set_policy(pol1, strlen(pol1));
	splen1 = ipsec_get_policylen(sp1);
	sp2 = ipsec_set_policy(pol2, strlen(pol2));
	splen2 = ipsec_get_policylen(sp2);

	if ((so = pfkey_open()) < 0)
		errx(1, "ERROR: %s", ipsec_strerror());

	printf("spdflush()\n");
	if (pfkey_send_spdflush(so) < 0)
		errx(1, "ERROR: %s", ipsec_strerror());
	m = pfkey_recv(so);
	free(m);

	printf("spdsetidx()\n");
	if (pfkey_send_spdsetidx(so, (struct sockaddr *)addr, 128,
				(struct sockaddr *)addr, 128,
				255, sp1, splen1, 0) < 0)
		errx(1, "ERROR: %s", ipsec_strerror());
	m = pfkey_recv(so);
	free(m);
	
	printf("spdupdate()\n");
	if (pfkey_send_spdupdate(so, (struct sockaddr *)addr, 128,
				(struct sockaddr *)addr, 128,
				255, sp2, splen2, 0) < 0)
		errx(1, "ERROR: %s", ipsec_strerror());
	m = pfkey_recv(so);
	free(m);

	printf("sleep(4)\n");
	sleep(4);

	printf("spddelete()\n");
	if (pfkey_send_spddelete(so, (struct sockaddr *)addr, 128,
				(struct sockaddr *)addr, 128,
				255, sp1, splen1, 0) < 0)
		errx(1, "ERROR: %s", ipsec_strerror());
	m = pfkey_recv(so);
	free(m);

	printf("spdadd()\n");
	if (pfkey_send_spdadd(so, (struct sockaddr *)addr, 128,
				(struct sockaddr *)addr, 128,
				255, sp2, splen2, 0) < 0)
		errx(1, "ERROR: %s", ipsec_strerror());
	spid = test2sub(so);

	printf("spdget(%u)\n", spid);
	if (pfkey_send_spdget(so, spid) < 0)
		errx(1, "ERROR: %s", ipsec_strerror());
	m = pfkey_recv(so);
	free(m);

	printf("sleep(4)\n");
	sleep(4);

	printf("spddelete2()\n");
	if (pfkey_send_spddelete2(so, spid) < 0)
		errx(1, "ERROR: %s", ipsec_strerror());
	m = pfkey_recv(so);
	free(m);

	printf("spdadd() with lifetime's 10(s)\n");
	if (pfkey_send_spdadd2(so, (struct sockaddr *)addr, 128,
				(struct sockaddr *)addr, 128,
				255, 0, 10, sp2, splen2, 0) < 0)
		errx(1, "ERROR: %s", ipsec_strerror());
	spid = test2sub(so);

	/* expecting failure */
	printf("spdupdate()\n");
	if (pfkey_send_spdupdate(so, (struct sockaddr *)addr, 128,
				(struct sockaddr *)addr, 128,
				255, sp2, splen2, 0) == 0) {
		warnx("ERROR: expecting failure.");
	}

	return 0;
}