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
struct torus {int dummy; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_hton64 (int /*<<< orphan*/ ) ; 
 char* strtok (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool parse_guid(struct torus *t, guid_t *guid, const char *parse_sep)
{
	char *val;
	bool success = false;

	val = strtok(NULL, parse_sep);
	if (!val)
		goto out;
	*guid = strtoull(val, NULL, 0);
	*guid = cl_hton64(*guid);

	success = true;
out:
	return success;
}