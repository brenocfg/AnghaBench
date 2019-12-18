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
typedef  int u32 ;
struct fw_device {int max_speed; int* config_rom; int config_rom_length; int max_rec; int cmc; int irmc; TYPE_1__* node; struct fw_card* card; } ;
struct fw_card {int link_speed; scalar_t__ beta_repeaters_present; } ;
struct TYPE_2__ {int max_speed; } ;

/* Variables and functions */
 int CSR_CONFIG_ROM ; 
 int CSR_REGISTER_BASE ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_CONFIG_ROM_SIZE ; 
 int RCODE_BUSY ; 
 int RCODE_COMPLETE ; 
 int SCODE_100 ; 
 int SCODE_BETA ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_device_rwsem ; 
 int /*<<< orphan*/  fw_err (struct fw_card*,char*,int,int) ; 
 int /*<<< orphan*/  kfree (int const*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int* kmemdup (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int read_rom (struct fw_device*,int,int,int*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_config_rom(struct fw_device *device, int generation)
{
	struct fw_card *card = device->card;
	const u32 *old_rom, *new_rom;
	u32 *rom, *stack;
	u32 sp, key;
	int i, end, length, ret;

	rom = kmalloc(sizeof(*rom) * MAX_CONFIG_ROM_SIZE +
		      sizeof(*stack) * MAX_CONFIG_ROM_SIZE, GFP_KERNEL);
	if (rom == NULL)
		return -ENOMEM;

	stack = &rom[MAX_CONFIG_ROM_SIZE];
	memset(rom, 0, sizeof(*rom) * MAX_CONFIG_ROM_SIZE);

	device->max_speed = SCODE_100;

	/* First read the bus info block. */
	for (i = 0; i < 5; i++) {
		ret = read_rom(device, generation, i, &rom[i]);
		if (ret != RCODE_COMPLETE)
			goto out;
		/*
		 * As per IEEE1212 7.2, during initialization, devices can
		 * reply with a 0 for the first quadlet of the config
		 * rom to indicate that they are booting (for example,
		 * if the firmware is on the disk of a external
		 * harddisk).  In that case we just fail, and the
		 * retry mechanism will try again later.
		 */
		if (i == 0 && rom[i] == 0) {
			ret = RCODE_BUSY;
			goto out;
		}
	}

	device->max_speed = device->node->max_speed;

	/*
	 * Determine the speed of
	 *   - devices with link speed less than PHY speed,
	 *   - devices with 1394b PHY (unless only connected to 1394a PHYs),
	 *   - all devices if there are 1394b repeaters.
	 * Note, we cannot use the bus info block's link_spd as starting point
	 * because some buggy firmwares set it lower than necessary and because
	 * 1394-1995 nodes do not have the field.
	 */
	if ((rom[2] & 0x7) < device->max_speed ||
	    device->max_speed == SCODE_BETA ||
	    card->beta_repeaters_present) {
		u32 dummy;

		/* for S1600 and S3200 */
		if (device->max_speed == SCODE_BETA)
			device->max_speed = card->link_speed;

		while (device->max_speed > SCODE_100) {
			if (read_rom(device, generation, 0, &dummy) ==
			    RCODE_COMPLETE)
				break;
			device->max_speed--;
		}
	}

	/*
	 * Now parse the config rom.  The config rom is a recursive
	 * directory structure so we parse it using a stack of
	 * references to the blocks that make up the structure.  We
	 * push a reference to the root directory on the stack to
	 * start things off.
	 */
	length = i;
	sp = 0;
	stack[sp++] = 0xc0000005;
	while (sp > 0) {
		/*
		 * Pop the next block reference of the stack.  The
		 * lower 24 bits is the offset into the config rom,
		 * the upper 8 bits are the type of the reference the
		 * block.
		 */
		key = stack[--sp];
		i = key & 0xffffff;
		if (WARN_ON(i >= MAX_CONFIG_ROM_SIZE)) {
			ret = -ENXIO;
			goto out;
		}

		/* Read header quadlet for the block to get the length. */
		ret = read_rom(device, generation, i, &rom[i]);
		if (ret != RCODE_COMPLETE)
			goto out;
		end = i + (rom[i] >> 16) + 1;
		if (end > MAX_CONFIG_ROM_SIZE) {
			/*
			 * This block extends outside the config ROM which is
			 * a firmware bug.  Ignore this whole block, i.e.
			 * simply set a fake block length of 0.
			 */
			fw_err(card, "skipped invalid ROM block %x at %llx\n",
			       rom[i],
			       i * 4 | CSR_REGISTER_BASE | CSR_CONFIG_ROM);
			rom[i] = 0;
			end = i;
		}
		i++;

		/*
		 * Now read in the block.  If this is a directory
		 * block, check the entries as we read them to see if
		 * it references another block, and push it in that case.
		 */
		for (; i < end; i++) {
			ret = read_rom(device, generation, i, &rom[i]);
			if (ret != RCODE_COMPLETE)
				goto out;

			if ((key >> 30) != 3 || (rom[i] >> 30) < 2)
				continue;
			/*
			 * Offset points outside the ROM.  May be a firmware
			 * bug or an Extended ROM entry (IEEE 1212-2001 clause
			 * 7.7.18).  Simply overwrite this pointer here by a
			 * fake immediate entry so that later iterators over
			 * the ROM don't have to check offsets all the time.
			 */
			if (i + (rom[i] & 0xffffff) >= MAX_CONFIG_ROM_SIZE) {
				fw_err(card,
				       "skipped unsupported ROM entry %x at %llx\n",
				       rom[i],
				       i * 4 | CSR_REGISTER_BASE | CSR_CONFIG_ROM);
				rom[i] = 0;
				continue;
			}
			stack[sp++] = i + rom[i];
		}
		if (length < i)
			length = i;
	}

	old_rom = device->config_rom;
	new_rom = kmemdup(rom, length * 4, GFP_KERNEL);
	if (new_rom == NULL) {
		ret = -ENOMEM;
		goto out;
	}

	down_write(&fw_device_rwsem);
	device->config_rom = new_rom;
	device->config_rom_length = length;
	up_write(&fw_device_rwsem);

	kfree(old_rom);
	ret = RCODE_COMPLETE;
	device->max_rec	= rom[2] >> 12 & 0xf;
	device->cmc	= rom[2] >> 30 & 1;
	device->irmc	= rom[2] >> 31 & 1;
 out:
	kfree(rom);

	return ret;
}