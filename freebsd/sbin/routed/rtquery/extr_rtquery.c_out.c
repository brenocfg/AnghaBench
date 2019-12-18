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
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  router ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  RIP_PORT ; 
 struct hostent* gethostbyname (char const*) ; 
 scalar_t__ gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  herror (char const*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_aton (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omsg_buf ; 
 int /*<<< orphan*/  omsg_len ; 
 int /*<<< orphan*/  perror (char const*) ; 
 scalar_t__ sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  sent ; 
 int /*<<< orphan*/  soc ; 

__attribute__((used)) static int
out(const char *host)
{
	struct sockaddr_in router;
	struct hostent *hp;

	if (gettimeofday(&sent, 0) < 0) {
		perror("gettimeofday(sent)");
		return -1;
	}

	memset(&router, 0, sizeof(router));
	router.sin_family = AF_INET;
#ifdef _HAVE_SIN_LEN
	router.sin_len = sizeof(router);
#endif
	if (!inet_aton(host, &router.sin_addr)) {
		hp = gethostbyname(host);
		if (hp == NULL) {
			herror(host);
			return -1;
		}
		memcpy(&router.sin_addr, hp->h_addr, sizeof(router.sin_addr));
	}
	router.sin_port = htons(RIP_PORT);

	if (sendto(soc, &omsg_buf, omsg_len, 0,
		   (struct sockaddr *)&router, sizeof(router)) < 0) {
		perror(host);
		return -1;
	}

	return 0;
}