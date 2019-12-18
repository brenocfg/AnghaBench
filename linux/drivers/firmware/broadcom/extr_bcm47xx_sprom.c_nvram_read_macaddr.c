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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int get_nvram_var (char const*,int /*<<< orphan*/ *,char const*,char*,int,int) ; 
 int /*<<< orphan*/  mac_pton (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 int /*<<< orphan*/  strreplace (char*,char,char) ; 

__attribute__((used)) static void nvram_read_macaddr(const char *prefix, const char *name,
			       u8 val[6], bool fallback)
{
	char buf[100];
	int err;

	err = get_nvram_var(prefix, NULL, name, buf, sizeof(buf), fallback);
	if (err < 0)
		return;

	strreplace(buf, '-', ':');
	if (!mac_pton(buf, val))
		pr_warn("Can not parse mac address: %s\n", buf);
}