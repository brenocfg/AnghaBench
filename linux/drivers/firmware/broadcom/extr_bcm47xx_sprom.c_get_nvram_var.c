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
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int ENOENT ; 
 int bcm47xx_nvram_getenv (char*,char*,int) ; 
 int /*<<< orphan*/  create_key (char const*,char const*,char const*,char*,int) ; 

__attribute__((used)) static int get_nvram_var(const char *prefix, const char *postfix,
			 const char *name, char *buf, int len, bool fallback)
{
	char key[40];
	int err;

	create_key(prefix, postfix, name, key, sizeof(key));

	err = bcm47xx_nvram_getenv(key, buf, len);
	if (fallback && err == -ENOENT && prefix) {
		create_key(NULL, postfix, name, key, sizeof(key));
		err = bcm47xx_nvram_getenv(key, buf, len);
	}
	return err;
}