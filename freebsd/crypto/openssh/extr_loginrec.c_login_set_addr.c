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
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sa; } ;
struct logininfo {TYPE_1__ hostaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr const*,unsigned int) ; 

void
login_set_addr(struct logininfo *li, const struct sockaddr *sa,
    const unsigned int sa_size)
{
	unsigned int bufsize = sa_size;

	/* make sure we don't overrun our union */
	if (sizeof(li->hostaddr) < sa_size)
		bufsize = sizeof(li->hostaddr);

	memcpy(&li->hostaddr.sa, sa, bufsize);
}