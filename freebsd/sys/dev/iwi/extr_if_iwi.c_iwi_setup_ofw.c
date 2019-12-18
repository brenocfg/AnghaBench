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
struct iwi_softc {int /*<<< orphan*/  sc_dev; } ;
struct iwi_fw {char const* data; int size; int /*<<< orphan*/  name; struct firmware* fp; } ;
struct iwi_firmware_ohdr {int /*<<< orphan*/  version; } ;
struct firmware {int datasize; int /*<<< orphan*/  name; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ IWI_FW_GET_MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ IWI_FW_GET_MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ IWI_FW_REQ_MAJOR ; 
 scalar_t__ IWI_FW_REQ_MINOR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct iwi_firmware_ohdr *
iwi_setup_ofw(struct iwi_softc *sc, struct iwi_fw *fw)
{
	const struct firmware *fp = fw->fp;
	const struct iwi_firmware_ohdr *hdr;

	if (fp->datasize < sizeof (struct iwi_firmware_ohdr)) {
		device_printf(sc->sc_dev, "image '%s' too small\n", fp->name);
		return NULL;
	}
	hdr = (const struct iwi_firmware_ohdr *)fp->data;
	if ((IWI_FW_GET_MAJOR(le32toh(hdr->version)) != IWI_FW_REQ_MAJOR) ||
	    (IWI_FW_GET_MINOR(le32toh(hdr->version)) != IWI_FW_REQ_MINOR)) {
		device_printf(sc->sc_dev, "version for '%s' %d.%d != %d.%d\n",
		    fp->name, IWI_FW_GET_MAJOR(le32toh(hdr->version)),
		    IWI_FW_GET_MINOR(le32toh(hdr->version)), IWI_FW_REQ_MAJOR,
		    IWI_FW_REQ_MINOR);
		return NULL;
	}
	fw->data = ((const char *) fp->data) + sizeof(struct iwi_firmware_ohdr);
	fw->size = fp->datasize - sizeof(struct iwi_firmware_ohdr);
	fw->name = fp->name;
	return hdr;
}