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
struct ebuf {scalar_t__ eb_magic; struct ebuf* eb_start; } ;

/* Variables and functions */
 scalar_t__ EBUF_MAGIC ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  free (struct ebuf*) ; 

void
ebuf_free(struct ebuf *eb)
{

	PJDLOG_ASSERT(eb != NULL && eb->eb_magic == EBUF_MAGIC);

	eb->eb_magic = 0;

	free(eb->eb_start);
	free(eb);
}