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
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_EVENT ; 
 int /*<<< orphan*/  CAP_READ ; 
 int /*<<< orphan*/  PF_ROUTE ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ caph_rights_limit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
rtsock_open(void)
{
	cap_rights_t rights;
	int error, s;

	s = socket(PF_ROUTE, SOCK_RAW, 0);
	if (s < 0)
		return (s);
	cap_rights_init(&rights, CAP_EVENT, CAP_READ);
	if (caph_rights_limit(s, &rights) != 0) {
		error = errno;
		(void)close(s);
		errno = errno;
		return (-1);
	}
	return (s);
}