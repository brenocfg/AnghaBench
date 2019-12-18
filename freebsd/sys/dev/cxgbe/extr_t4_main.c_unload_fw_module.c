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
struct firmware {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 int /*<<< orphan*/  firmware_put (struct firmware const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unload_fw_module(struct adapter *sc, const struct firmware *dcfg,
    const struct firmware *fw)
{

	if (fw != NULL)
		firmware_put(fw, FIRMWARE_UNLOAD);
	if (dcfg != NULL)
		firmware_put(dcfg, FIRMWARE_UNLOAD);
}