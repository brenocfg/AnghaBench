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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ctl_putuint (char*,int) ; 
 int rand () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
send_random_tag_value(
	int	indx
	)
{
	int	noise;
	char	buf[32];

	noise = rand() ^ (rand() << 16);
	buf[0] = 'a' + noise % 26;
	noise >>= 5;
	buf[1] = 'a' + noise % 26;
	noise >>= 5;
	buf[2] = 'a' + noise % 26;
	noise >>= 5;
	buf[3] = '.';
	snprintf(&buf[4], sizeof(buf) - 4, "%d", indx);
	ctl_putuint(buf, noise);
}