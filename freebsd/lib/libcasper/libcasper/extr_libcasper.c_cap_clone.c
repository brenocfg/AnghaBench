#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_7__ {scalar_t__ cch_magic; int /*<<< orphan*/  cch_flags; } ;
typedef  TYPE_1__ cap_channel_t ;

/* Variables and functions */
 scalar_t__ CAP_CHANNEL_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* cap_wrap (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cap_xfer_nvlist (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_nvlist_flags (TYPE_1__ const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/ *,char*) ; 
 int nvlist_take_descriptor (int /*<<< orphan*/ *,char*) ; 

cap_channel_t *
cap_clone(const cap_channel_t *chan)
{
	cap_channel_t *newchan;
	nvlist_t *nvl;
	int newsock;

	assert(chan != NULL);
	assert(chan->cch_magic == CAP_CHANNEL_MAGIC);

	nvl = nvlist_create(channel_nvlist_flags(chan));
	nvlist_add_string(nvl, "cmd", "clone");
	nvl = cap_xfer_nvlist(chan, nvl);
	if (nvl == NULL)
		return (NULL);
	if (nvlist_get_number(nvl, "error") != 0) {
		errno = (int)nvlist_get_number(nvl, "error");
		nvlist_destroy(nvl);
		return (NULL);
	}
	newsock = nvlist_take_descriptor(nvl, "sock");
	nvlist_destroy(nvl);
	newchan = cap_wrap(newsock, chan->cch_flags);
	if (newchan == NULL) {
		int serrno;

		serrno = errno;
		close(newsock);
		errno = serrno;
	}

	return (newchan);
}