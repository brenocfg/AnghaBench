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
struct lio_recv_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct lio_recv_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
lio_free_recv_info(struct lio_recv_info *recv_info)
{

	free(recv_info, M_DEVBUF);
}