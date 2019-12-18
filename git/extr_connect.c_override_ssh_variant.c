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
typedef  enum ssh_variant { ____Placeholder_ssh_variant } ssh_variant ;

/* Variables and functions */
 int VARIANT_AUTO ; 
 int VARIANT_PLINK ; 
 int VARIANT_PUTTY ; 
 int VARIANT_SIMPLE ; 
 int VARIANT_SSH ; 
 int VARIANT_TORTOISEPLINK ; 
 char* getenv (char*) ; 
 scalar_t__ git_config_get_string_const (char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void override_ssh_variant(enum ssh_variant *ssh_variant)
{
	const char *variant = getenv("GIT_SSH_VARIANT");

	if (!variant && git_config_get_string_const("ssh.variant", &variant))
		return;

	if (!strcmp(variant, "auto"))
		*ssh_variant = VARIANT_AUTO;
	else if (!strcmp(variant, "plink"))
		*ssh_variant = VARIANT_PLINK;
	else if (!strcmp(variant, "putty"))
		*ssh_variant = VARIANT_PUTTY;
	else if (!strcmp(variant, "tortoiseplink"))
		*ssh_variant = VARIANT_TORTOISEPLINK;
	else if (!strcmp(variant, "simple"))
		*ssh_variant = VARIANT_SIMPLE;
	else
		*ssh_variant = VARIANT_SSH;
}