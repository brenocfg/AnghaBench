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
struct shallow_info {int dummy; } ;
struct async {int in; int /*<<< orphan*/  proc; } ;
typedef  int /*<<< orphan*/  muxer ;

/* Variables and functions */
 int /*<<< orphan*/  KEEPALIVE_AFTER_NUL ; 
 int /*<<< orphan*/  copy_to_sideband ; 
 int /*<<< orphan*/  finish_async (struct async*) ; 
 int /*<<< orphan*/  memset (struct async*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ start_async (struct async*) ; 
 char const* unpack (int,struct shallow_info*) ; 
 int /*<<< orphan*/  use_keepalive ; 
 int /*<<< orphan*/  use_sideband ; 

__attribute__((used)) static const char *unpack_with_sideband(struct shallow_info *si)
{
	struct async muxer;
	const char *ret;

	if (!use_sideband)
		return unpack(0, si);

	use_keepalive = KEEPALIVE_AFTER_NUL;
	memset(&muxer, 0, sizeof(muxer));
	muxer.proc = copy_to_sideband;
	muxer.in = -1;
	if (start_async(&muxer))
		return NULL;

	ret = unpack(muxer.in, si);

	finish_async(&muxer);
	return ret;
}