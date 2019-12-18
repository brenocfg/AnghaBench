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
struct rtas_manage_flash_t {int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ rtas_busy_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  rtas_token (char*) ; 

__attribute__((used)) static void manage_flash(struct rtas_manage_flash_t *args_buf, unsigned int op)
{
	s32 rc;

	do {
		rc = rtas_call(rtas_token("ibm,manage-flash-image"), 1, 1,
			       NULL, op);
	} while (rtas_busy_delay(rc));

	args_buf->status = rc;
}