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
struct termios {int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_iflag; int /*<<< orphan*/  c_cflag; } ;
struct modes {int /*<<< orphan*/  set; int /*<<< orphan*/  unset; scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ CHK (char*,scalar_t__) ; 
 struct modes* cmodes ; 
 struct modes* imodes ; 
 struct modes* lmodes ; 
 struct modes* omodes ; 

int
msearch(char *str, struct termios *ip)
{
	struct modes *mp;

	for (mp = cmodes; mp->name; ++mp)
		if (CHK(str, mp->name)) {
			ip->c_cflag &= ~mp->unset;
			ip->c_cflag |= mp->set;
			return (1);
		}
	for (mp = imodes; mp->name; ++mp)
		if (CHK(str, mp->name)) {
			ip->c_iflag &= ~mp->unset;
			ip->c_iflag |= mp->set;
			return (1);
		}
	for (mp = lmodes; mp->name; ++mp)
		if (CHK(str, mp->name)) {
			ip->c_lflag &= ~mp->unset;
			ip->c_lflag |= mp->set;
			return (1);
		}
	for (mp = omodes; mp->name; ++mp)
		if (CHK(str, mp->name)) {
			ip->c_oflag &= ~mp->unset;
			ip->c_oflag |= mp->set;
			return (1);
		}
	return (0);
}