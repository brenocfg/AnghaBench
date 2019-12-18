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
typedef  int /*<<< orphan*/  tsdn_t ;

/* Variables and functions */
 int /*<<< orphan*/  TSDN_NULL ; 
 int /*<<< orphan*/  arena_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* iallocztm (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  sz_size2index (size_t) ; 

__attribute__((used)) static char *
prof_thread_name_alloc(tsdn_t *tsdn, const char *thread_name) {
	char *ret;
	size_t size;

	if (thread_name == NULL) {
		return NULL;
	}

	size = strlen(thread_name) + 1;
	if (size == 1) {
		return "";
	}

	ret = iallocztm(tsdn, size, sz_size2index(size), false, NULL, true,
	    arena_get(TSDN_NULL, 0, true), true);
	if (ret == NULL) {
		return NULL;
	}
	memcpy(ret, thread_name, size);
	return ret;
}