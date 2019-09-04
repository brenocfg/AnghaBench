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
 char* current_config_name () ; 
 char* current_config_origin_type () ; 
 int /*<<< orphan*/  current_config_scope () ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* scope_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iterate_cb(const char *var, const char *value, void *data)
{
	static int nr;

	if (nr++)
		putchar('\n');

	printf("key=%s\n", var);
	printf("value=%s\n", value ? value : "(null)");
	printf("origin=%s\n", current_config_origin_type());
	printf("name=%s\n", current_config_name());
	printf("scope=%s\n", scope_name(current_config_scope()));

	return 0;
}