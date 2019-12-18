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
typedef  int u_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int get_match (char const*,int /*<<< orphan*/ ) ; 
 int get_pfxmatch (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logcfg_class ; 
 int /*<<< orphan*/  logcfg_class_items ; 
 int /*<<< orphan*/  logcfg_noclass_items ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static u_int32
get_logmask(
	const char *	str
	)
{
	const char *	t;
	u_int32		offset;
	u_int32		mask;

	mask = get_match(str, logcfg_noclass_items);
	if (mask != 0)
		return mask;

	t = str;
	offset = get_pfxmatch(&t, logcfg_class);
	mask   = get_match(t, logcfg_class_items);

	if (mask)
		return mask << offset;
	else
		msyslog(LOG_ERR, "logconfig: '%s' not recognized - ignored",
			str);

	return 0;
}