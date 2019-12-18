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

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int recv_sideband (char*,int,int) ; 

__attribute__((used)) static int sideband_demux(int in, int out, void *data)
{
	int *xd = data;
	int ret;

	ret = recv_sideband("fetch-pack", xd[0], out);
	close(out);
	return ret;
}