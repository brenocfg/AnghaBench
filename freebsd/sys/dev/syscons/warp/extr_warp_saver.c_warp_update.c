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
typedef  int /*<<< orphan*/  video_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  SET_ORIGIN (int /*<<< orphan*/ *,int) ; 
 int SPP ; 
 int banksize ; 
 int bpsl ; 
 int scrh ; 
 int scrw ; 
 int* star ; 
 int* vid ; 

__attribute__((used)) static void
warp_update(video_adapter_t *adp)
{
	int i, j, k, n, o, p;
	int last_origin = -1;

	for (i = 1, k = 0, n = SPP*8; i < 5; i++, n /= 2) {
		for (j = 0; j < n; j++, k++) {
			p = (star[k] / scrw) *  bpsl + (star[k] % scrw);
			o = 0;
			while (p > banksize) {
				p -= banksize;
				o += banksize;
			}
			SET_ORIGIN(adp, o);
			vid[p] = 0;
			star[k] += i;
			if (star[k] > scrw*scrh)
				star[k] -= scrw*scrh;
			p = (star[k] / scrw) *  bpsl + (star[k] % scrw);
			o = 0;
			while (p > banksize) {
				p -= banksize;
				o += banksize;
			}
			SET_ORIGIN(adp, o);
			vid[p] = i;
		}
	}
}