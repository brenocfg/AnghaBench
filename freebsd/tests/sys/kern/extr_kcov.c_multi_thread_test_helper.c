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
struct multi_thread_data {size_t mode; int /*<<< orphan*/  thread; int /*<<< orphan*/ * buf; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char*,...) ; 
 int /*<<< orphan*/  KIOENABLE ; 
 scalar_t__ atomic_load_64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 char** modes ; 
 size_t nitems (char**) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
multi_thread_test_helper(void *ptr)
{
	struct multi_thread_data *data = ptr;

	ATF_REQUIRE_MSG(ioctl(data->fd, KIOENABLE, data->mode) == 0,
	    "Unable to enable kcov %s in thread %d",
	    data->mode < nitems(modes) ? modes[data->mode] : "unknown mode",
	    data->thread);

	atomic_store_64(&data->buf[0], 0);
	sleep(0);
	ATF_REQUIRE_MSG(atomic_load_64(&data->buf[0]) != 0,
	    "No records found in thread %d", data->thread);

	return (NULL);
}