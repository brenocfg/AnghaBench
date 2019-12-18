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
typedef  int /*<<< orphan*/  uint8_t ;
struct manage_flash_t {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 struct manage_flash_t manage_flash_data ; 
 int /*<<< orphan*/  opal_manage_flash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void opal_flash_manage(uint8_t op)
{
	struct manage_flash_t *const args_buf = &manage_flash_data;

	args_buf->status = opal_manage_flash(op);
}