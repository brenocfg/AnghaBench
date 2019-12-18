#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct file_lock* n_bytes; } ;
struct TYPE_4__ {struct file_lock* n_bytes; } ;
struct TYPE_5__ {TYPE_1__ oh; } ;
struct file_lock {TYPE_3__ client_cookie; TYPE_2__ client; struct file_lock* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct file_lock*) ; 

void
deallocate_file_lock(struct file_lock *fl)
{
	free(fl->addr);
	free(fl->client.oh.n_bytes);
	free(fl->client_cookie.n_bytes);
	free(fl);
}