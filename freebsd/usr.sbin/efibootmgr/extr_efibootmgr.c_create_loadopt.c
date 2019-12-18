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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  const* efidp ;
typedef  int /*<<< orphan*/  const efi_char ;
typedef  int /*<<< orphan*/  attributes ;

/* Variables and functions */
 size_t BAD_LENGTH ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  le16enc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  le32enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  utf8_to_ucs2 (char const*,int /*<<< orphan*/  const**,size_t*) ; 

__attribute__((used)) static size_t
create_loadopt(uint8_t *buf, size_t bufmax, uint32_t attributes, efidp dp, size_t dp_size,
    const char *description, const uint8_t *optional_data, size_t optional_data_size)
{
	efi_char *bbuf = NULL;
	uint8_t *pos = buf;
	size_t desc_len = 0;
	size_t len;

	if (optional_data == NULL && optional_data_size != 0)
		return BAD_LENGTH;
	if (dp == NULL && dp_size != 0)
		return BAD_LENGTH;

	/*
	 * Compute the length to make sure the passed in buffer is long enough.
	 */
	utf8_to_ucs2(description, &bbuf, &desc_len);
	len = sizeof(uint32_t) + sizeof(uint16_t) + desc_len + dp_size + optional_data_size;
	if (len > bufmax) {
		free(bbuf);
		return BAD_LENGTH;
	}

	le32enc(pos, attributes);
	pos += sizeof (attributes);

	le16enc(pos, dp_size);
	pos += sizeof (uint16_t);

	memcpy(pos, bbuf, desc_len);	/* NB:desc_len includes strailing NUL */
	pos += desc_len;
	free(bbuf);

	memcpy(pos, dp, dp_size);
	pos += dp_size;

	if (optional_data && optional_data_size > 0) {
		memcpy(pos, optional_data, optional_data_size);
		pos += optional_data_size;
	}

	return pos - buf;
}