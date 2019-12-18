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
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int quote_c_style (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static void print_path_1(const char *path)
{
	int need_quote = quote_c_style(path, NULL, NULL, 0);
	if (need_quote)
		quote_c_style(path, NULL, stdout, 0);
	else if (strchr(path, ' '))
		printf("\"%s\"", path);
	else
		printf("%s", path);
}