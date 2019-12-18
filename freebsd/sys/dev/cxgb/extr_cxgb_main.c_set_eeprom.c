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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int u32 ;
struct port_info {struct adapter* adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int t3_seeprom_read (struct adapter*,int,int*) ; 
 int t3_seeprom_wp (struct adapter*,int) ; 
 int t3_seeprom_write (struct adapter*,int,int) ; 

__attribute__((used)) static int
set_eeprom(struct port_info *pi, const uint8_t *data, int len, int offset)
{
	uint8_t *buf;
	int err = 0;
	u32 aligned_offset, aligned_len, *p;
	struct adapter *adapter = pi->adapter;


	aligned_offset = offset & ~3;
	aligned_len = (len + (offset & 3) + 3) & ~3;

	if (aligned_offset != offset || aligned_len != len) {
		buf = malloc(aligned_len, M_DEVBUF, M_WAITOK|M_ZERO);		   
		if (!buf)
			return (ENOMEM);
		err = t3_seeprom_read(adapter, aligned_offset, (u32 *)buf);
		if (!err && aligned_len > 4)
			err = t3_seeprom_read(adapter,
					      aligned_offset + aligned_len - 4,
					      (u32 *)&buf[aligned_len - 4]);
		if (err)
			goto out;
		memcpy(buf + (offset & 3), data, len);
	} else
		buf = (uint8_t *)(uintptr_t)data;

	err = t3_seeprom_wp(adapter, 0);
	if (err)
		goto out;

	for (p = (u32 *)buf; !err && aligned_len; aligned_len -= 4, p++) {
		err = t3_seeprom_write(adapter, aligned_offset, *p);
		aligned_offset += 4;
	}

	if (!err)
		err = t3_seeprom_wp(adapter, 1);
out:
	if (buf != data)
		free(buf, M_DEVBUF);
	return err;
}