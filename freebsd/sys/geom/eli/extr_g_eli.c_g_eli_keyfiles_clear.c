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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * preload_fetch_addr (int /*<<< orphan*/ *) ; 
 size_t preload_fetch_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * preload_search_by_type (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 

__attribute__((used)) static void
g_eli_keyfiles_clear(const char *provider)
{
	u_char *keyfile, *data;
	char name[64];
	size_t size;
	int i;

	for (i = 0; ; i++) {
		snprintf(name, sizeof(name), "%s:geli_keyfile%d", provider, i);
		keyfile = preload_search_by_type(name);
		if (keyfile == NULL)
			return;
		data = preload_fetch_addr(keyfile);
		size = preload_fetch_size(keyfile);
		if (data != NULL && size != 0)
			bzero(data, size);
	}
}