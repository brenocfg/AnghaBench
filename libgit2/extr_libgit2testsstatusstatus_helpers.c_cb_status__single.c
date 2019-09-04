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
struct TYPE_2__ {int count; unsigned int status; scalar_t__ debug; } ;
typedef  TYPE_1__ status_entry_single ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char const*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

int cb_status__single(const char *p, unsigned int s, void *payload)
{
	status_entry_single *data = (status_entry_single *)payload;

	if (data->debug)
		fprintf(stderr, "%02d: %s (%04x)\n", data->count, p, s);

	data->count++;
	data->status = s;

	return 0;
}