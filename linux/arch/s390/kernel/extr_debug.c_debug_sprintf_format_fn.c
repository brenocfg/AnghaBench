#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct debug_view {int dummy; } ;
struct TYPE_5__ {char* string; int /*<<< orphan*/ * args; } ;
typedef  TYPE_1__ debug_sprintf_entry_t ;
struct TYPE_6__ {int buf_size; } ;
typedef  TYPE_2__ debug_info_t ;

/* Variables and functions */
 int DEBUG_SPRINTF_MAX_ARGS ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int debug_sprintf_format_fn(debug_info_t *id, struct debug_view *view,
				   char *out_buf, debug_sprintf_entry_t *curr_event)
{
	int num_longs, num_used_args = 0, i, rc = 0;
	int index[DEBUG_SPRINTF_MAX_ARGS];

	/* count of longs fit into one entry */
	num_longs = id->buf_size / sizeof(long);

	if (num_longs < 1)
		goto out; /* bufsize of entry too small */
	if (num_longs == 1) {
		/* no args, we use only the string */
		strcpy(out_buf, curr_event->string);
		rc = strlen(curr_event->string);
		goto out;
	}

	/* number of arguments used for sprintf (without the format string) */
	num_used_args = min(DEBUG_SPRINTF_MAX_ARGS, (num_longs - 1));

	memset(index, 0, DEBUG_SPRINTF_MAX_ARGS * sizeof(int));

	for (i = 0; i < num_used_args; i++)
		index[i] = i;

	rc = sprintf(out_buf, curr_event->string, curr_event->args[index[0]],
		     curr_event->args[index[1]], curr_event->args[index[2]],
		     curr_event->args[index[3]], curr_event->args[index[4]],
		     curr_event->args[index[5]], curr_event->args[index[6]],
		     curr_event->args[index[7]], curr_event->args[index[8]],
		     curr_event->args[index[9]]);
out:
	return rc;
}