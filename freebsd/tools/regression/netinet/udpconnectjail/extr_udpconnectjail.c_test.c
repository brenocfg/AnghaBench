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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test(const char *context, struct sockaddr_in *sin)
{
	int sock;

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
		errx(-1, "%s: socket(PF_INET, SOCK_DGRAM, 0): %s", context,
		    strerror(errno));

	if (connect(sock, (struct sockaddr *)sin, sizeof(*sin)) < 0)
		errx(-1, "%s: connect(%s): %s", context,
		    inet_ntoa(sin->sin_addr), strerror(errno));

	if (close(sock) < 0)
		errx(-1, "%s: close(): %s", context, strerror(errno));
}