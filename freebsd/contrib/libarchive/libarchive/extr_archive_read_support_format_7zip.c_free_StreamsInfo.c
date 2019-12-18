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
struct _7z_stream_info {int /*<<< orphan*/  ss; int /*<<< orphan*/  ci; int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_CodersInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_PackInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_SubStreamsInfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_StreamsInfo(struct _7z_stream_info *si)
{
	free_PackInfo(&(si->pi));
	free_CodersInfo(&(si->ci));
	free_SubStreamsInfo(&(si->ss));
}