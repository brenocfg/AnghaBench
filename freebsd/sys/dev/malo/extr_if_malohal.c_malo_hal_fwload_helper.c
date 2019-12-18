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
struct malo_hal {int /*<<< orphan*/  mh_dev; } ;
struct firmware {int /*<<< orphan*/  datasize; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 int /*<<< orphan*/  MALO_NOWAIT ; 
 int /*<<< orphan*/  MALO_WAITOK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,...) ; 
 struct firmware* firmware_get (char*) ; 
 int /*<<< orphan*/  firmware_put (struct firmware const*,int /*<<< orphan*/ ) ; 
 int malo_hal_send_helper (struct malo_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
malo_hal_fwload_helper(struct malo_hal *mh, char *helper)
{
	const struct firmware *fw;
	int error;

	fw = firmware_get(helper);
	if (fw == NULL) {
		device_printf(mh->mh_dev, "could not read microcode %s!\n",
		    helper);
		return (EIO);
	}

	device_printf(mh->mh_dev, "load %s firmware image (%zu bytes)\n",
	    helper, fw->datasize);

	error = malo_hal_send_helper(mh, fw->datasize, fw->data, fw->datasize,
		MALO_WAITOK);
	if (error != 0)
		goto fail;

	/* tell the card we're done and... */
	error = malo_hal_send_helper(mh, 0, NULL, 0, MALO_NOWAIT);

fail:
	firmware_put(fw, FIRMWARE_UNLOAD);

	return (error);
}