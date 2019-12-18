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
struct stream_filter {TYPE_1__* vtbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (struct stream_filter*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct stream_filter*) ; 

void free_stream_filter(struct stream_filter *filter)
{
	filter->vtbl->free(filter);
}