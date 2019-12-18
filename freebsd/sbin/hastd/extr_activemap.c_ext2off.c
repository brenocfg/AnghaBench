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
struct activemap {int am_nextents; int am_extentshift; int am_mediasize; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 

__attribute__((used)) static __inline off_t
ext2off(const struct activemap *amp, int extent)
{
	off_t offset;

	PJDLOG_ASSERT(extent >= 0 && extent < amp->am_nextents);
	offset = ((off_t)extent << amp->am_extentshift);
	PJDLOG_ASSERT(offset >= 0 && offset < amp->am_mediasize);
	return (offset);
}