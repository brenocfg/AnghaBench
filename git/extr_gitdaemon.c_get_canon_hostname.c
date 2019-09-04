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
struct TYPE_2__ {char const* buf; } ;
struct hostinfo {TYPE_1__ canon_hostname; } ;

/* Variables and functions */
 int /*<<< orphan*/  lookup_hostname (struct hostinfo*) ; 

__attribute__((used)) static const char *get_canon_hostname(struct hostinfo *hi)
{
	lookup_hostname(hi);
	return hi->canon_hostname.buf;
}