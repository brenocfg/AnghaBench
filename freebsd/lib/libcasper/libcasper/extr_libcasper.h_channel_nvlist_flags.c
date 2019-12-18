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
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int CASPER_NO_UNIQ ; 
 int NV_FLAG_NO_UNIQUE ; 
 int cap_channel_flags (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int
channel_nvlist_flags(const cap_channel_t *chan)
{
	int flags;

	flags = 0;
	if ((cap_channel_flags(chan) & CASPER_NO_UNIQ) != 0)
		flags |= NV_FLAG_NO_UNIQUE;

	return (flags);
}