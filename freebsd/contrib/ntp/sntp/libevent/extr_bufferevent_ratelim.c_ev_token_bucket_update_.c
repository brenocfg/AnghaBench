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
struct ev_token_bucket_cfg {unsigned int read_maximum; unsigned int read_rate; unsigned int write_maximum; unsigned int write_rate; } ;
struct ev_token_bucket {void* last_updated; unsigned int read_limit; unsigned int write_limit; } ;
typedef  void* ev_uint32_t ;

/* Variables and functions */
 unsigned int INT_MAX ; 

int
ev_token_bucket_update_(struct ev_token_bucket *bucket,
    const struct ev_token_bucket_cfg *cfg,
    ev_uint32_t current_tick)
{
	/* It's okay if the tick number overflows, since we'll just
	 * wrap around when we do the unsigned substraction. */
	unsigned n_ticks = current_tick - bucket->last_updated;

	/* Make sure some ticks actually happened, and that time didn't
	 * roll back. */
	if (n_ticks == 0 || n_ticks > INT_MAX)
		return 0;

	/* Naively, we would say
		bucket->limit += n_ticks * cfg->rate;

		if (bucket->limit > cfg->maximum)
			bucket->limit = cfg->maximum;

	   But we're worried about overflow, so we do it like this:
	*/

	if ((cfg->read_maximum - bucket->read_limit) / n_ticks < cfg->read_rate)
		bucket->read_limit = cfg->read_maximum;
	else
		bucket->read_limit += n_ticks * cfg->read_rate;


	if ((cfg->write_maximum - bucket->write_limit) / n_ticks < cfg->write_rate)
		bucket->write_limit = cfg->write_maximum;
	else
		bucket->write_limit += n_ticks * cfg->write_rate;


	bucket->last_updated = current_tick;

	return 1;
}