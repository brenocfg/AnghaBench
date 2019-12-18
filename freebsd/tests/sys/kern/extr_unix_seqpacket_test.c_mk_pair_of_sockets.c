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
typedef  int /*<<< orphan*/  sun ;
struct sockaddr_un {int sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  ATF_CHECK_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_un*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static const char*
mk_pair_of_sockets(int *sv)
{
	struct sockaddr_un sun;
	/* ATF's isolation mechanisms will guarantee uniqueness of this file */
	const char *path = "sock";
	int s, err, s2, s1;

	s = socket(PF_LOCAL, SOCK_SEQPACKET, 0);
	ATF_REQUIRE(s >= 0);

	bzero(&sun, sizeof(sun));
	sun.sun_family = AF_LOCAL;
	sun.sun_len = sizeof(sun);
	strlcpy(sun.sun_path, path, sizeof(sun.sun_path));
	err = bind(s, (struct sockaddr *)&sun, sizeof(sun));
	err = listen(s, -1);
	ATF_CHECK_EQ(0, err);

	/* Create the other socket */
	s2 = socket(PF_LOCAL, SOCK_SEQPACKET, 0);
	ATF_REQUIRE(s2 >= 0);
	err = connect(s2, (struct sockaddr*)&sun, sizeof(sun));
	if (err != 0) {
		perror("connect");
		atf_tc_fail("connect(2) failed");
	}

	/* Accept it */
	s1 = accept(s, NULL, NULL);
	if (s1 == -1) {
		perror("accept");
		atf_tc_fail("accept(2) failed");
	}

	sv[0] = s1;
	sv[1] = s2;

	close(s);

	return (path);
}