#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* buf; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int IDENT_NAME_GIVEN ; 
 int /*<<< orphan*/  copy_gecos (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  default_name_is_bogus ; 
 TYPE_1__ git_default_name ; 
 int ident_config_given ; 
 int /*<<< orphan*/  strbuf_trim (TYPE_1__*) ; 
 int /*<<< orphan*/  xgetpwuid_self (int /*<<< orphan*/ *) ; 

const char *ident_default_name(void)
{
	if (!(ident_config_given & IDENT_NAME_GIVEN) && !git_default_name.len) {
		copy_gecos(xgetpwuid_self(&default_name_is_bogus), &git_default_name);
		strbuf_trim(&git_default_name);
	}
	return git_default_name.buf;
}