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
typedef  scalar_t__ timestamp_t ;
struct rerere_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ rerere_created_at (struct rerere_id*) ; 
 scalar_t__ rerere_last_used_at (struct rerere_id*) ; 
 int /*<<< orphan*/  unlink_rr_item (struct rerere_id*) ; 

__attribute__((used)) static void prune_one(struct rerere_id *id,
		      timestamp_t cutoff_resolve, timestamp_t cutoff_noresolve)
{
	timestamp_t then;
	timestamp_t cutoff;

	then = rerere_last_used_at(id);
	if (then)
		cutoff = cutoff_resolve;
	else {
		then = rerere_created_at(id);
		if (!then)
			return;
		cutoff = cutoff_noresolve;
	}
	if (then < cutoff)
		unlink_rr_item(id);
}