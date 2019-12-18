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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int ITERATIONS ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  bzero (struct sockaddr_un*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_path ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
datagram_client(void)
{
	struct sockaddr_un sun;
	ssize_t len;
	char c = 0;
	int fd, i;

	bzero(&sun, sizeof(sun));
	sun.sun_len = sizeof(sun);
	sun.sun_family = AF_UNIX;
	strcpy(sun.sun_path, socket_path);
	for (i = 0; i < ITERATIONS; i++) {
		fd = socket(PF_UNIX, SOCK_DGRAM, 0);
		if (fd < 0) {
			warn("datagram_client: socket");
			return;
		}
		len = sendto(fd, &c, sizeof(c), 0, (struct sockaddr *)&sun,
		    sizeof(sun));
		if (len < 0)
			warn("datagram_client: sendto");
		close(fd);
	}
}