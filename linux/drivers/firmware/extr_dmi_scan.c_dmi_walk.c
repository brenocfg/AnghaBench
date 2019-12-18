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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  dmi_available ; 
 int /*<<< orphan*/  dmi_base ; 
 int /*<<< orphan*/  dmi_decode_table (int /*<<< orphan*/ *,void (*) (struct dmi_header const*,void*),void*) ; 
 int /*<<< orphan*/  dmi_len ; 
 int /*<<< orphan*/ * dmi_remap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmi_unmap (int /*<<< orphan*/ *) ; 

int dmi_walk(void (*decode)(const struct dmi_header *, void *),
	     void *private_data)
{
	u8 *buf;

	if (!dmi_available)
		return -ENXIO;

	buf = dmi_remap(dmi_base, dmi_len);
	if (buf == NULL)
		return -ENOMEM;

	dmi_decode_table(buf, decode, private_data);

	dmi_unmap(buf);
	return 0;
}