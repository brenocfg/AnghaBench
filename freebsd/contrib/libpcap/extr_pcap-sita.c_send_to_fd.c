#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fd; int find_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIND ; 
 int /*<<< orphan*/  LIVE ; 
 int /*<<< orphan*/  close_with_IOP (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_unit (int,int) ; 
 int /*<<< orphan*/  find_unit_by_fd (int,int*,int*,int /*<<< orphan*/ *) ; 
 TYPE_1__** units ; 
 int write (int,unsigned char*,int) ; 

__attribute__((used)) static void send_to_fd(int fd, int len, unsigned char *str) {
	int		nwritten;
	int		chassis, geoslot;

	while (len > 0) {
		if ((nwritten = write(fd, str, len)) <= 0) {
			find_unit_by_fd(fd, &chassis, &geoslot, NULL);
			if (units[chassis][geoslot].fd == fd)			close_with_IOP(chassis, geoslot, LIVE);
			else if (units[chassis][geoslot].find_fd == fd)	close_with_IOP(chassis, geoslot, FIND);
			empty_unit(chassis, geoslot);
			return;
		}
		len -= nwritten;
		str += nwritten;
	}
}