#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bt3c_info {TYPE_2__* p_dev; } ;
typedef  int /*<<< orphan*/  b ;
struct TYPE_4__ {TYPE_1__** resource; } ;
struct TYPE_3__ {unsigned int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 scalar_t__ CONTROL ; 
 int EFAULT ; 
 int EILSEQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  bt3c_address (unsigned int,int) ; 
 int /*<<< orphan*/  bt3c_io_write (unsigned int,int,int) ; 
 int /*<<< orphan*/  bt3c_put (unsigned int,unsigned int) ; 
 int inb (scalar_t__) ; 
 scalar_t__ kstrtouint (char*,int,unsigned int*) ; 
 scalar_t__ kstrtoul (char*,int,unsigned long*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bt3c_load_firmware(struct bt3c_info *info,
			      const unsigned char *firmware,
			      int count)
{
	char *ptr = (char *) firmware;
	char b[9];
	unsigned int iobase, tmp, tn;
	unsigned long size, addr, fcs;
	int i, err = 0;

	iobase = info->p_dev->resource[0]->start;

	/* Reset */
	bt3c_io_write(iobase, 0x8040, 0x0404);
	bt3c_io_write(iobase, 0x8040, 0x0400);

	udelay(1);

	bt3c_io_write(iobase, 0x8040, 0x0404);

	udelay(17);

	/* Load */
	while (count) {
		if (ptr[0] != 'S') {
			BT_ERR("Bad address in firmware");
			err = -EFAULT;
			goto error;
		}

		memset(b, 0, sizeof(b));
		memcpy(b, ptr + 2, 2);
		if (kstrtoul(b, 16, &size) < 0)
			return -EINVAL;

		memset(b, 0, sizeof(b));
		memcpy(b, ptr + 4, 8);
		if (kstrtoul(b, 16, &addr) < 0)
			return -EINVAL;

		memset(b, 0, sizeof(b));
		memcpy(b, ptr + (size * 2) + 2, 2);
		if (kstrtoul(b, 16, &fcs) < 0)
			return -EINVAL;

		memset(b, 0, sizeof(b));
		for (tmp = 0, i = 0; i < size; i++) {
			memcpy(b, ptr + (i * 2) + 2, 2);
			if (kstrtouint(b, 16, &tn))
				return -EINVAL;
			tmp += tn;
		}

		if (((tmp + fcs) & 0xff) != 0xff) {
			BT_ERR("Checksum error in firmware");
			err = -EILSEQ;
			goto error;
		}

		if (ptr[1] == '3') {
			bt3c_address(iobase, addr);

			memset(b, 0, sizeof(b));
			for (i = 0; i < (size - 4) / 2; i++) {
				memcpy(b, ptr + (i * 4) + 12, 4);
				if (kstrtouint(b, 16, &tmp))
					return -EINVAL;
				bt3c_put(iobase, tmp);
			}
		}

		ptr   += (size * 2) + 6;
		count -= (size * 2) + 6;
	}

	udelay(17);

	/* Boot */
	bt3c_address(iobase, 0x3000);
	outb(inb(iobase + CONTROL) | 0x40, iobase + CONTROL);

error:
	udelay(17);

	/* Clear */
	bt3c_io_write(iobase, 0x7006, 0x0000);
	bt3c_io_write(iobase, 0x7005, 0x0000);
	bt3c_io_write(iobase, 0x7001, 0x0000);

	return err;
}