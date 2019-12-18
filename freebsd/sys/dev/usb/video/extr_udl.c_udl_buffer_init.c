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
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udl_buffer_head ; 
 int /*<<< orphan*/  udl_buffer_mtx ; 

__attribute__((used)) static void
udl_buffer_init(void *arg)
{
	mtx_init(&udl_buffer_mtx, "USB", "UDL", MTX_DEF);
	TAILQ_INIT(&udl_buffer_head);
}