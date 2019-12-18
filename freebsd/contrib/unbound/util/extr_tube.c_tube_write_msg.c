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
typedef  char uint8_t ;
typedef  int uint32_t ;
struct tube {int sw; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fd_set_block (int) ; 
 int /*<<< orphan*/  fd_set_nonblock (int) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int write (int,...) ; 

int tube_write_msg(struct tube* tube, uint8_t* buf, uint32_t len, 
        int nonblock)
{
	ssize_t r, d;
	int fd = tube->sw;

	/* test */
	if(nonblock) {
		r = write(fd, &len, sizeof(len));
		if(r == -1) {
			if(errno==EINTR || errno==EAGAIN)
				return -1;
			log_err("tube msg write failed: %s", strerror(errno));
			return -1; /* can still continue, perhaps */
		}
	} else r = 0;
	if(!fd_set_block(fd))
		return 0;
	/* write remainder */
	d = r;
	while(d != (ssize_t)sizeof(len)) {
		if((r=write(fd, ((char*)&len)+d, sizeof(len)-d)) == -1) {
			if(errno == EAGAIN)
				continue; /* temporarily unavail: try again*/
			log_err("tube msg write failed: %s", strerror(errno));
			(void)fd_set_nonblock(fd);
			return 0;
		}
		d += r;
	}
	d = 0;
	while(d != (ssize_t)len) {
		if((r=write(fd, buf+d, len-d)) == -1) {
			if(errno == EAGAIN)
				continue; /* temporarily unavail: try again*/
			log_err("tube msg write failed: %s", strerror(errno));
			(void)fd_set_nonblock(fd);
			return 0;
		}
		d += r;
	}
	if(!fd_set_nonblock(fd))
		return 0;
	return 1;
}