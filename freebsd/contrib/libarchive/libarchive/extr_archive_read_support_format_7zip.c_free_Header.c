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
struct _7z_header_info {int /*<<< orphan*/  attrBools; int /*<<< orphan*/  antiBools; int /*<<< orphan*/  emptyFileBools; int /*<<< orphan*/  emptyStreamBools; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_Header(struct _7z_header_info *h)
{
	free(h->emptyStreamBools);
	free(h->emptyFileBools);
	free(h->antiBools);
	free(h->attrBools);
}