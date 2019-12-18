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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  tmp ;
struct atmel_sha_dev {int flags; scalar_t__ io_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SHA_FLAGS_DUMP_REG ; 
 int /*<<< orphan*/  atmel_sha_reg_name (scalar_t__,char*,int,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void atmel_sha_write(struct atmel_sha_dev *dd,
					u32 offset, u32 value)
{
#ifdef VERBOSE_DEBUG
	if (dd->flags & SHA_FLAGS_DUMP_REG) {
		char tmp[16];

		dev_vdbg(dd->dev, "write 0x%08x into %s\n", value,
			 atmel_sha_reg_name(offset, tmp, sizeof(tmp), true));
	}
#endif /* VERBOSE_DEBUG */

	writel_relaxed(value, dd->io_base + offset);
}