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
struct debug_view {int dummy; } ;
typedef  int /*<<< orphan*/  debug_info_t ;
typedef  int /*<<< orphan*/  debug_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int debug_raw_header_fn(debug_info_t *id, struct debug_view *view,
			       int area, debug_entry_t *entry, char *out_buf)
{
	int rc;

	rc = sizeof(debug_entry_t);
	memcpy(out_buf, entry, sizeof(debug_entry_t));
	return rc;
}