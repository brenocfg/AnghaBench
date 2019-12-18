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
typedef  enum bufferevent_flush_mode { ____Placeholder_bufferevent_flush_mode } bufferevent_flush_mode ;

/* Variables and functions */
#define  BEV_FINISHED 130 
#define  BEV_FLUSH 129 
#define  BEV_NORMAL 128 
 int Z_FINISH ; 
 int Z_NO_FLUSH ; 
 int Z_SYNC_FLUSH ; 

__attribute__((used)) static int
getstate(enum bufferevent_flush_mode state)
{
	switch (state) {
	case BEV_FINISHED:
		return Z_FINISH;
	case BEV_FLUSH:
		return Z_SYNC_FLUSH;
	case BEV_NORMAL:
	default:
		return Z_NO_FLUSH;
	}
}