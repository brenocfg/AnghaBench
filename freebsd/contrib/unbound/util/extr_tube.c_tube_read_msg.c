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
struct tube {int sr; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fd_set_block (int) ; 
 int /*<<< orphan*/  fd_set_nonblock (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 scalar_t__ malloc (int) ; 
 int read (int,...) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

int tube_read_msg(struct tube* tube, uint8_t** buf, uint32_t* len, 
        int nonblock)
{
	ssize_t r, d;
	int fd = tube->sr;

	/* test */
	*len = 0;
	if(nonblock) {
		r = read(fd, len, sizeof(*len));
		if(r == -1) {
			if(errno==EINTR || errno==EAGAIN)
				return -1;
			log_err("tube msg read failed: %s", strerror(errno));
			return -1; /* we can still continue, perhaps */
		}
		if(r == 0) /* EOF */
			return 0;
	} else r = 0;
	if(!fd_set_block(fd))
		return 0;
	/* read remainder */
	d = r;
	while(d != (ssize_t)sizeof(*len)) {
		if((r=read(fd, ((char*)len)+d, sizeof(*len)-d)) == -1) {
			log_err("tube msg read failed: %s", strerror(errno));
			(void)fd_set_nonblock(fd);
			return 0;
		}
		if(r == 0) /* EOF */ {
			(void)fd_set_nonblock(fd);
			return 0;
		}
		d += r;
	}
	log_assert(*len < 65536*2);
	*buf = (uint8_t*)malloc(*len);
	if(!*buf) {
		log_err("tube read out of memory");
		(void)fd_set_nonblock(fd);
		return 0;
	}
	d = 0;
	while(d < (ssize_t)*len) {
		if((r=read(fd, (*buf)+d, (size_t)((ssize_t)*len)-d)) == -1) {
			log_err("tube msg read failed: %s", strerror(errno));
			(void)fd_set_nonblock(fd);
			free(*buf);
			return 0;
		}
		if(r == 0) { /* EOF */
			(void)fd_set_nonblock(fd);
			free(*buf);
			return 0;
		}
		d += r;
	}
	if(!fd_set_nonblock(fd)) {
		free(*buf);
		return 0;
	}
	return 1;
}