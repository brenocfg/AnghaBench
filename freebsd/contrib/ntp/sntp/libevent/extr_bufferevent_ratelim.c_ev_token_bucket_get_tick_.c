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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct ev_token_bucket_cfg {int msec_per_tick; } ;
typedef  int ev_uint64_t ;
typedef  unsigned int ev_uint32_t ;

/* Variables and functions */

ev_uint32_t
ev_token_bucket_get_tick_(const struct timeval *tv,
    const struct ev_token_bucket_cfg *cfg)
{
	/* This computation uses two multiplies and a divide.  We could do
	 * fewer if we knew that the tick length was an integer number of
	 * seconds, or if we knew it divided evenly into a second.  We should
	 * investigate that more.
	 */

	/* We cast to an ev_uint64_t first, since we don't want to overflow
	 * before we do the final divide. */
	ev_uint64_t msec = (ev_uint64_t)tv->tv_sec * 1000 + tv->tv_usec / 1000;
	return (unsigned)(msec / cfg->msec_per_tick);
}