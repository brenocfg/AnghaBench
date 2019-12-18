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
typedef  int /*<<< orphan*/  umad_ca_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,char const*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  TRACE (char*,char const*) ; 
 scalar_t__ find_cached_ca (char const*,int /*<<< orphan*/ *) ; 
 int get_ca (char const*,int /*<<< orphan*/ *) ; 
 char* resolve_ca_name (char const*,int /*<<< orphan*/ *) ; 

int umad_get_ca(const char *ca_name, umad_ca_t * ca)
{
	int r;

	TRACE("ca_name %s", ca_name);
	if (!(ca_name = resolve_ca_name(ca_name, NULL)))
		return -ENODEV;

	if (find_cached_ca(ca_name, ca) > 0)
		return 0;

	if ((r = get_ca(ca_name, ca)) < 0)
		return r;

	DEBUG("opened %s", ca_name);
	return 0;
}