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
struct stream_filter {int dummy; } ;
struct cascade_filter {int /*<<< orphan*/  two; int /*<<< orphan*/  one; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct stream_filter*) ; 
 int /*<<< orphan*/  free_stream_filter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cascade_free_fn(struct stream_filter *filter)
{
	struct cascade_filter *cas = (struct cascade_filter *)filter;
	free_stream_filter(cas->one);
	free_stream_filter(cas->two);
	free(filter);
}