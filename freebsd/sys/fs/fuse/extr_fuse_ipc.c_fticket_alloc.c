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
struct fuse_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  ticket_zone ; 
 struct fuse_ticket* uma_zalloc_arg (int /*<<< orphan*/ ,struct fuse_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct fuse_ticket *
fticket_alloc(struct fuse_data *data)
{
	return uma_zalloc_arg(ticket_zone, data, M_WAITOK);
}