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
struct grep_source {int type; int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
#define  GREP_SOURCE_BUF 130 
#define  GREP_SOURCE_FILE 129 
#define  GREP_SOURCE_OID 128 

void grep_source_clear_data(struct grep_source *gs)
{
	switch (gs->type) {
	case GREP_SOURCE_FILE:
	case GREP_SOURCE_OID:
		FREE_AND_NULL(gs->buf);
		gs->size = 0;
		break;
	case GREP_SOURCE_BUF:
		/* leave user-provided buf intact */
		break;
	}
}