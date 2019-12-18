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
struct passwd {int /*<<< orphan*/ * pw_shell; int /*<<< orphan*/ * pw_dir; int /*<<< orphan*/ * pw_gecos; int /*<<< orphan*/ * pw_class; int /*<<< orphan*/ * pw_passwd; int /*<<< orphan*/ * pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct passwd*,struct passwd const*,int) ; 
 void* strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clone_passwd(struct passwd *dest, struct passwd const *src)
{
	ATF_REQUIRE(dest != NULL);
	ATF_REQUIRE(src != NULL);

	memcpy(dest, src, sizeof(struct passwd));
	if (src->pw_name != NULL)
		dest->pw_name = strdup(src->pw_name);
	if (src->pw_passwd != NULL)
		dest->pw_passwd = strdup(src->pw_passwd);
	if (src->pw_class != NULL)
		dest->pw_class = strdup(src->pw_class);
	if (src->pw_gecos != NULL)
		dest->pw_gecos = strdup(src->pw_gecos);
	if (src->pw_dir != NULL)
		dest->pw_dir = strdup(src->pw_dir);
	if (src->pw_shell != NULL)
		dest->pw_shell = strdup(dest->pw_shell);
}