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

/* Variables and functions */
 char const* _ (int /*<<< orphan*/ ) ; 
 char* expand_user_path (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_exists (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  implicit_ident_advice_config ; 
 int /*<<< orphan*/  implicit_ident_advice_noconfig ; 
 char* xdg_config_home (char*) ; 

__attribute__((used)) static const char *implicit_ident_advice(void)
{
	char *user_config = expand_user_path("~/.gitconfig", 0);
	char *xdg_config = xdg_config_home("config");
	int config_exists = file_exists(user_config) || file_exists(xdg_config);

	free(user_config);
	free(xdg_config);

	if (config_exists)
		return _(implicit_ident_advice_config);
	else
		return _(implicit_ident_advice_noconfig);

}