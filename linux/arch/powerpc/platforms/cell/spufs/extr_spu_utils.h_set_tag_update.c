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
 int /*<<< orphan*/  MFC_WrTagUpdate ; 
 int /*<<< orphan*/  spu_writech (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void set_tag_update(void)
{
	unsigned int update_any = 1;

	/* Save, Step 15:
	 * Restore, Step 8:
	 *    Write the MFC_TagUpdate channel with '01'.
	 */
	spu_writech(MFC_WrTagUpdate, update_any);
}