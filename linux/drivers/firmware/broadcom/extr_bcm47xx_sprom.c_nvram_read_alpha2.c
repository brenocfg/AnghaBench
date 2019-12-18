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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int get_nvram_var (char const*,int /*<<< orphan*/ *,char const*,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void nvram_read_alpha2(const char *prefix, const char *name,
			     char val[2], bool fallback)
{
	char buf[10];
	int err;

	err = get_nvram_var(prefix, NULL, name, buf, sizeof(buf), fallback);
	if (err < 0)
		return;
	if (buf[0] == '0')
		return;
	if (strlen(buf) > 2) {
		pr_warn("alpha2 is too long %s\n", buf);
		return;
	}
	memcpy(val, buf, 2);
}