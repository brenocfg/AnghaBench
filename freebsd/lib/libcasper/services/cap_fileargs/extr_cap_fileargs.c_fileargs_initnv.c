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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fileargs_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  cap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cap_init () ; 
 int /*<<< orphan*/ * fileargs_cinitnv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fileargs_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 

fileargs_t *
fileargs_initnv(nvlist_t *limits)
{
        cap_channel_t *cas;
	fileargs_t *fa;

	if (limits == NULL) {
		return (fileargs_create(NULL, 0));
	}

        cas = cap_init();
        if (cas == NULL) {
		nvlist_destroy(limits);
                return (NULL);
	}

        fa = fileargs_cinitnv(cas, limits);
        cap_close(cas);

	return (fa);
}