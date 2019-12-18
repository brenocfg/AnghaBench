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
 int /*<<< orphan*/  DUMBUFLEN ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  MAXRETRY ; 
 int /*<<< orphan*/  TIOCCDTR ; 
 int /*<<< orphan*/  TIOCSDTR ; 
 char* dumbuf ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
hay_sync(void)
{
	int len, retry = 0;

	while (retry++ <= MAXRETRY) {
		write(FD, "AT\r", 3);
		sleep(1);
		ioctl(FD, FIONREAD, &len);
		if (len) {
			len = read(FD, dumbuf, min(len, DUMBUFLEN));
			if (strchr(dumbuf, '0') || 
		   	(strchr(dumbuf, 'O') && strchr(dumbuf, 'K')))
				return(1);
#ifdef DEBUG
			dumbuf[len] = '\0';
			printf("hay_sync: (\"%s\") %d\n\r", dumbuf, retry);
#endif
		}
		ioctl(FD, TIOCCDTR, 0);
		ioctl(FD, TIOCSDTR, 0);
	}
	printf("Cannot synchronize with hayes...\n\r");
	return(0);
}