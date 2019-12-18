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
typedef  int /*<<< orphan*/  unit_t ;

/* Variables and functions */
 int /*<<< orphan*/  find_unit_by_fd (int,int*,int*,int /*<<< orphan*/ **) ; 
 int recv (int,unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_client_nbytes(int fd, int count, unsigned char *buf) {
	unit_t			*u;
	int				chassis, geoslot;
	int				len;

	find_unit_by_fd(fd, &chassis, &geoslot, &u);
	while (count) {
		if ((len = recv(fd, buf, count, 0)) <= 0)	return -1;	/* read in whatever data was sent to us */
		count -= len;
		buf += len;
	}															/* till we have everything we are looking for */
	return 0;
}