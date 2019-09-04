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
struct transport {int verbose; int family; scalar_t__ progress; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  TRANSPORT_FAMILY_ALL 130 
#define  TRANSPORT_FAMILY_IPV4 129 
#define  TRANSPORT_FAMILY_IPV6 128 
 int /*<<< orphan*/  set_helper_option (struct transport*,char*,char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int) ; 

__attribute__((used)) static void standard_options(struct transport *t)
{
	char buf[16];
	int v = t->verbose;

	set_helper_option(t, "progress", t->progress ? "true" : "false");

	xsnprintf(buf, sizeof(buf), "%d", v + 1);
	set_helper_option(t, "verbosity", buf);

	switch (t->family) {
	case TRANSPORT_FAMILY_ALL:
		/*
		 * this is already the default,
		 * do not break old remote helpers by setting "all" here
		 */
		break;
	case TRANSPORT_FAMILY_IPV4:
		set_helper_option(t, "family", "ipv4");
		break;
	case TRANSPORT_FAMILY_IPV6:
		set_helper_option(t, "family", "ipv6");
		break;
	}
}