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
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 char* thr_getspecific (int /*<<< orphan*/ ) ; 
 scalar_t__ thr_main () ; 
 scalar_t__ thr_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ thr_setspecific (int /*<<< orphan*/ ,char*) ; 
 char* ttyname_buf ; 
 int /*<<< orphan*/  ttyname_init_once ; 
 int /*<<< orphan*/  ttyname_key ; 
 int /*<<< orphan*/  ttyname_keycreate ; 
 int /*<<< orphan*/  ttyname_keycreated ; 
 scalar_t__ ttyname_r (int,char*,int) ; 

char *
ttyname(int fd)
{
	char	*buf;

	if (thr_main() != 0)
		buf = ttyname_buf;
	else {
		if (thr_once(&ttyname_init_once, ttyname_keycreate) != 0 ||
		    !ttyname_keycreated)
			return (NULL);
		if ((buf = thr_getspecific(ttyname_key)) == NULL) {
			if ((buf = malloc(sizeof ttyname_buf)) == NULL)
				return (NULL);
			if (thr_setspecific(ttyname_key, buf) != 0) {
				free(buf);
				return (NULL);
			}
		}
	}

	if (ttyname_r(fd, buf, sizeof ttyname_buf) != 0)
		return (NULL);
	return (buf);
}