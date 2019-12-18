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
struct fuse_ticket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ticket_zone ; 
 void uma_zfree (int /*<<< orphan*/ ,struct fuse_ticket*) ; 

__attribute__((used)) static inline void
fticket_destroy(struct fuse_ticket *ftick)
{
	return uma_zfree(ticket_zone, ftick);
}