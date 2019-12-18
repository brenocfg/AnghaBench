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
struct program_bidder {int dummy; } ;
struct archive_read_filter_bidder {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free_state (struct program_bidder*) ; 

__attribute__((used)) static int
program_bidder_free(struct archive_read_filter_bidder *self)
{
	struct program_bidder *state = (struct program_bidder *)self->data;

	free_state(state);
	return (ARCHIVE_OK);
}