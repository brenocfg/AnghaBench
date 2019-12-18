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
typedef  int u_int ;
typedef  char u_char ;

/* Variables and functions */
 char* preload_fetch_addr (void*) ; 
 int preload_fetch_size (void*) ; 
 void* preload_search_by_type (char*) ; 

__attribute__((used)) static void
vm_page_blacklist_load(char **list, char **end)
{
	void *mod;
	u_char *ptr;
	u_int len;

	mod = NULL;
	ptr = NULL;

	mod = preload_search_by_type("ram_blacklist");
	if (mod != NULL) {
		ptr = preload_fetch_addr(mod);
		len = preload_fetch_size(mod);
        }
	*list = ptr;
	if (ptr != NULL)
		*end = ptr + len;
	else
		*end = NULL;
	return;
}