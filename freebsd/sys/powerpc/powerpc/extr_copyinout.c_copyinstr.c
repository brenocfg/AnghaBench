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
 int EFAULT ; 
 int ENAMETOOLONG ; 
 int fubyte (int /*<<< orphan*/ ) ; 

int
copyinstr(const void *udaddr, void *kaddr, size_t len, size_t *done)
{
	const char	*up;
	char		*kp;
	size_t		l;
	int		rv, c;

	kp = kaddr;
	up = udaddr;

	rv = ENAMETOOLONG;

	for (l = 0; len-- > 0; l++) {
		if ((c = fubyte(up++)) < 0) {
			rv = EFAULT;
			break;
		}

		if (!(*kp++ = c)) {
			l++;
			rv = 0;
			break;
		}
	}

	if (done != NULL) {
		*done = l;
	}

	return (rv);
}