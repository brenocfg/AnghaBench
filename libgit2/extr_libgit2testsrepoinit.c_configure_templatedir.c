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
 int /*<<< orphan*/  create_tmp_global_config (char*,char*,char const*) ; 

__attribute__((used)) static void configure_templatedir(const char *template_path)
{
	create_tmp_global_config("tmp_global_path", "init.templatedir", template_path);
}