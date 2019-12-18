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
struct rerere_id {scalar_t__ variant; } ;

/* Variables and functions */
 char const* git_path (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rerere_id_hex (struct rerere_id const*) ; 

const char *rerere_path(const struct rerere_id *id, const char *file)
{
	if (!file)
		return git_path("rr-cache/%s", rerere_id_hex(id));

	if (id->variant <= 0)
		return git_path("rr-cache/%s/%s", rerere_id_hex(id), file);

	return git_path("rr-cache/%s/%s.%d",
			rerere_id_hex(id), file, id->variant);
}