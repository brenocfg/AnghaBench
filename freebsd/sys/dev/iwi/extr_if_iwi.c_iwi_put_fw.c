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
struct iwi_fw {int /*<<< orphan*/ * name; scalar_t__ size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 int /*<<< orphan*/  firmware_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwi_put_fw(struct iwi_fw *fw)
{
	if (fw->fp != NULL) {
		firmware_put(fw->fp, FIRMWARE_UNLOAD);
		fw->fp = NULL;
	}
	fw->data = NULL;
	fw->size = 0;
	fw->name = NULL;
}