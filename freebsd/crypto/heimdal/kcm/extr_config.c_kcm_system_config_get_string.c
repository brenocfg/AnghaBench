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
 int /*<<< orphan*/  kcm_context ; 
 char const* krb5_config_get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
kcm_system_config_get_string(const char *string)
{
    return krb5_config_get_string(kcm_context, NULL, "kcm",
				  "system_ccache", string, NULL);
}