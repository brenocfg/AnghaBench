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
struct mqueue_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MQUEUEDATA ; 
 int /*<<< orphan*/  free (struct mqueue_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
mqueue_freemsg(struct mqueue_msg *msg)
{
	free(msg, M_MQUEUEDATA);
}