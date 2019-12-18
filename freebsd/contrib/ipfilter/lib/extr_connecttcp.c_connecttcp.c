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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {int /*<<< orphan*/ * h_addr_list; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ ISDIGIT (char) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int inet_aton (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
connecttcp(char *server, int port)
{
	struct sockaddr_in sin;
	struct hostent *host;
	int fd;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port & 65535);

	if (ISDIGIT(*server)) {
		if (inet_aton(server, &sin.sin_addr) == -1) {
			return -1;
		}
	} else {
		host = gethostbyname(server);
		if (host == NULL)
			return -1;
		memcpy(&sin.sin_addr, host->h_addr_list[0],
		       sizeof(sin.sin_addr));
	}

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		return -1;

	if (connect(fd, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
		close(fd);
		return -1;
	}

	return fd;
}