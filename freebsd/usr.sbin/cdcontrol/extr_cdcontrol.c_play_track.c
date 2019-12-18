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
struct ioc_play_track {int start_track; int start_index; int end_track; int end_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDIOCPLAYTRACKS ; 
 int /*<<< orphan*/  fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ioc_play_track*) ; 

__attribute__((used)) static int
play_track(int tstart, int istart, int tend, int iend)
{
	struct ioc_play_track t;

	t.start_track = tstart;
	t.start_index = istart;
	t.end_track = tend;
	t.end_index = iend;

	return ioctl (fd, CDIOCPLAYTRACKS, &t);
}