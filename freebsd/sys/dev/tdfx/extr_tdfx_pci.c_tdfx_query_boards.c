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
 int tdfx_count ; 

__attribute__((used)) static int
tdfx_query_boards(void) {
	/* 
    *	This returns the number of installed tdfx cards, we have been keeping
	 * count, look at tdfx_attach 
	 */
	return tdfx_count;
}