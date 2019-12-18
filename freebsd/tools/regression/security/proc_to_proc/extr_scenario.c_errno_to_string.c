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

/* Variables and functions */
#define  EACCES 133 
#define  EINVAL 132 
#define  ENOSYS 131 
#define  EOPNOTSUPP 130 
#define  EPERM 129 
#define  ESRCH 128 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static char *
errno_to_string(int error)
{

	switch (error) {
	case EPERM:
		return ("EPERM");
	case EACCES:
		return ("EACCES");
	case EINVAL:
		return ("EINVAL");
	case ENOSYS:
		return ("ENOSYS");
	case ESRCH:
		return ("ESRCH");
	case EOPNOTSUPP:
		return ("EOPNOTSUPP");
	case 0:
		return ("0");
	default:
		printf("%d\n", error);
		return ("unknown");
	}
}