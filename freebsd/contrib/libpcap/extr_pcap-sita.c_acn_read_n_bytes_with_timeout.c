#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  r_fds ;
struct TYPE_3__ {int fd; int /*<<< orphan*/ * bp; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int recv (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int acn_read_n_bytes_with_timeout(pcap_t *handle, int count) {
	struct		timeval tv;
	int			retval, fd;
	fd_set		r_fds;
	fd_set		w_fds;
	u_char		*bp;
	int			len = 0;
	int			offset = 0;

	tv.tv_sec = 5;
	tv.tv_usec = 0;

	fd = handle->fd;
	FD_ZERO(&r_fds);
	FD_SET(fd, &r_fds);
	memcpy(&w_fds, &r_fds, sizeof(r_fds));
	bp = handle->bp;
	while (count) {
		retval = select(fd + 1, &w_fds, NULL, NULL, &tv);
		if (retval == -1) {											/* an error occured !!!!! */
//			fprintf(stderr, "error during packet data read\n");
			return -1;												/* but we need to return a good indication to prevent unneccessary popups */
		} else if (retval == 0) {									/* timeout occured, so process what we've got sofar and return */
//			fprintf(stderr, "timeout during packet data read\n");
			return -1;
		} else {
			if ((len = recv(fd, (bp + offset), count, 0)) <= 0) {
//				fprintf(stderr, "premature exit during packet data rx\n");
				return -1;
			}
			count -= len;
			offset += len;
		}
	}
	return 0;
}