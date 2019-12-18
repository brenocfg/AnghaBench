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
struct passwd {int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_gecos; int /*<<< orphan*/  pw_passwd; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct passwd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
compat_clear_template(struct passwd *template)
{

	free(template->pw_passwd);
	free(template->pw_gecos);
	free(template->pw_dir);
	free(template->pw_shell);
	memset(template, 0, sizeof(*template));
}