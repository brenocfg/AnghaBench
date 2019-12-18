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
struct uuid {int dummy; } ;
struct g_part_uuid_alias {struct uuid* uuid; int /*<<< orphan*/  alias; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EQUUID (struct uuid*,int /*<<< orphan*/ *) ; 
 char* g_part_alias_name (int /*<<< orphan*/ ) ; 
 struct g_part_uuid_alias* gpt_uuid_alias_match ; 
 int /*<<< orphan*/  gpt_uuid_unused ; 
 int parse_uuid (char const*,struct uuid*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char const*) ; 

__attribute__((used)) static int
gpt_parse_type(const char *type, struct uuid *uuid)
{
	struct uuid tmp;
	const char *alias;
	int error;
	struct g_part_uuid_alias *uap;

	if (type[0] == '!') {
		error = parse_uuid(type + 1, &tmp);
		if (error)
			return (error);
		if (EQUUID(&tmp, &gpt_uuid_unused))
			return (EINVAL);
		*uuid = tmp;
		return (0);
	}
	for (uap = &gpt_uuid_alias_match[0]; uap->uuid; uap++) {
		alias = g_part_alias_name(uap->alias);
		if (!strcasecmp(type, alias)) {
			*uuid = *uap->uuid;
			return (0);
		}
	}
	return (EINVAL);
}