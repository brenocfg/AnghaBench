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
typedef  enum cover_from_description { ____Placeholder_cover_from_description } cover_from_description ;

/* Variables and functions */
 int COVER_FROM_AUTO ; 
 int COVER_FROM_MESSAGE ; 
 int COVER_FROM_NONE ; 
 int COVER_FROM_SUBJECT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum cover_from_description parse_cover_from_description(const char *arg)
{
	if (!arg || !strcmp(arg, "default"))
		return COVER_FROM_MESSAGE;
	else if (!strcmp(arg, "none"))
		return COVER_FROM_NONE;
	else if (!strcmp(arg, "message"))
		return COVER_FROM_MESSAGE;
	else if (!strcmp(arg, "subject"))
		return COVER_FROM_SUBJECT;
	else if (!strcmp(arg, "auto"))
		return COVER_FROM_AUTO;
	else
		die(_("%s: invalid cover from description mode"), arg);
}