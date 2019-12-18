#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_3__ {char* thread_name; } ;
typedef  TYPE_1__ prof_tdata_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  idalloctm (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  isblank (char) ; 
 int /*<<< orphan*/  isgraph (char) ; 
 TYPE_1__* prof_tdata_get (int /*<<< orphan*/ *,int) ; 
 char* prof_thread_name_alloc (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ tsd_reentrancy_level_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

int
prof_thread_name_set(tsd_t *tsd, const char *thread_name) {
	assert(tsd_reentrancy_level_get(tsd) == 0);

	prof_tdata_t *tdata;
	unsigned i;
	char *s;

	tdata = prof_tdata_get(tsd, true);
	if (tdata == NULL) {
		return EAGAIN;
	}

	/* Validate input. */
	if (thread_name == NULL) {
		return EFAULT;
	}
	for (i = 0; thread_name[i] != '\0'; i++) {
		char c = thread_name[i];
		if (!isgraph(c) && !isblank(c)) {
			return EFAULT;
		}
	}

	s = prof_thread_name_alloc(tsd_tsdn(tsd), thread_name);
	if (s == NULL) {
		return EAGAIN;
	}

	if (tdata->thread_name != NULL) {
		idalloctm(tsd_tsdn(tsd), tdata->thread_name, NULL, NULL, true,
		    true);
		tdata->thread_name = NULL;
	}
	if (strlen(s) > 0) {
		tdata->thread_name = s;
	}
	return 0;
}