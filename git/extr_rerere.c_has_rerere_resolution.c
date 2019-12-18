#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rerere_id {int variant; TYPE_1__* collection; } ;
struct TYPE_2__ {int const* status; } ;

/* Variables and functions */
 int RR_HAS_POSTIMAGE ; 
 int RR_HAS_PREIMAGE ; 

__attribute__((used)) static int has_rerere_resolution(const struct rerere_id *id)
{
	const int both = RR_HAS_POSTIMAGE|RR_HAS_PREIMAGE;
	int variant = id->variant;

	if (variant < 0)
		return 0;
	return ((id->collection->status[variant] & both) == both);
}