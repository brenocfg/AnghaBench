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
struct request {int wbt_flags; } ;

/* Variables and functions */
 int WBT_READ ; 

__attribute__((used)) static inline bool wbt_is_read(struct request *rq)
{
	return rq->wbt_flags & WBT_READ;
}