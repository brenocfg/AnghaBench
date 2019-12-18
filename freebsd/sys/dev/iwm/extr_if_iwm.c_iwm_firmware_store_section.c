#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {struct iwm_fw_img* img; } ;
struct iwm_softc {TYPE_1__ sc_fw; } ;
struct iwm_fw_img {size_t fw_count; struct iwm_fw_desc* sec; } ;
struct iwm_fw_desc {size_t len; int /*<<< orphan*/  const* data; int /*<<< orphan*/  offset; } ;
typedef  enum iwm_ucode_type { ____Placeholder_iwm_ucode_type } iwm_ucode_type ;

/* Variables and functions */
 int EINVAL ; 
 size_t IWM_UCODE_SECTION_MAX ; 
 int IWM_UCODE_TYPE_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
iwm_firmware_store_section(struct iwm_softc *sc,
    enum iwm_ucode_type type, const uint8_t *data, size_t dlen)
{
	struct iwm_fw_img *fws;
	struct iwm_fw_desc *fwone;

	if (type >= IWM_UCODE_TYPE_MAX)
		return EINVAL;
	if (dlen < sizeof(uint32_t))
		return EINVAL;

	fws = &sc->sc_fw.img[type];
	if (fws->fw_count >= IWM_UCODE_SECTION_MAX)
		return EINVAL;

	fwone = &fws->sec[fws->fw_count];

	/* first 32bit are device load offset */
	memcpy(&fwone->offset, data, sizeof(uint32_t));

	/* rest is data */
	fwone->data = data + sizeof(uint32_t);
	fwone->len = dlen - sizeof(uint32_t);

	fws->fw_count++;

	return 0;
}