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
struct ib_wq {int /*<<< orphan*/  uobject; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_uobj_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_wq_read(struct ib_wq *wq)
{
	put_uobj_read(wq->uobject);
}