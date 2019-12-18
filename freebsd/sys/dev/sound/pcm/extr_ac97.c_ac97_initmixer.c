#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  int u_int32_t ;
struct ac97_info {scalar_t__ count; int flags; unsigned int caps; unsigned int se; int id; int subvendor; unsigned int extcaps; unsigned int extid; int extstat; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_2__* mix; scalar_t__ noext; int /*<<< orphan*/  devinfo; int /*<<< orphan*/  methods; } ;
typedef  int /*<<< orphan*/  (* ac97_patch ) (struct ac97_info*) ;
struct TYPE_6__ {int id; int stepmask; char* name; int /*<<< orphan*/  (* patch ) (struct ac97_info*) ;scalar_t__ noext; } ;
struct TYPE_5__ {int enable; int reg; unsigned int bits; int ofs; scalar_t__ mute; } ;
struct TYPE_4__ {int id; char* name; } ;

/* Variables and functions */
 int AC97_EXTCAPS ; 
 int AC97_F_EAPD_INV ; 
 int AC97_F_RDCD_BUG ; 
 scalar_t__ AC97_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int AC97_MIXER_SIZE ; 
 int AC97_MIX_BEEP ; 
 int AC97_MIX_TONE ; 
 int AC97_REGEXT_ID ; 
 int AC97_REGEXT_STAT ; 
 int AC97_REG_ID1 ; 
 int AC97_REG_ID2 ; 
 int AC97_REG_POWER ; 
 int AC97_REG_RESET ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENODEV ; 
 size_t SOUND_MIXER_VOLUME ; 
 int /*<<< orphan*/  ac97_fix_auxout (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_fix_tone (struct ac97_info*) ; 
 unsigned int ac97_hw_desc (int,char const*,char const*,char*) ; 
 int ac97_rdcd (struct ac97_info*,int) ; 
 int /*<<< orphan*/  ac97_reset (struct ac97_info*) ; 
 int /*<<< orphan*/  ac97_wrcd (struct ac97_info*,int,unsigned int) ; 
 TYPE_3__* ac97codecid ; 
 int /*<<< orphan*/ * ac97enhancement ; 
 int /*<<< orphan*/ * ac97extfeature ; 
 int /*<<< orphan*/ * ac97feature ; 
 TYPE_2__* ac97mixtable_default ; 
 TYPE_1__* ac97vendorid ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ pci_get_subdevice (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subvendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
ac97_initmixer(struct ac97_info *codec)
{
	ac97_patch codec_patch;
	const char *cname, *vname;
	char desc[80];
	u_int8_t model, step;
	unsigned i, j, k, bit, old;
	u_int32_t id;
	int reg;

	snd_mtxlock(codec->lock);
	codec->count = AC97_INIT(codec->methods, codec->devinfo);
	if (codec->count == 0) {
		device_printf(codec->dev, "ac97 codec init failed\n");
		snd_mtxunlock(codec->lock);
		return ENODEV;
	}

	ac97_wrcd(codec, AC97_REG_POWER, (codec->flags & AC97_F_EAPD_INV)? 0x8000 : 0x0000);
	ac97_reset(codec);
	ac97_wrcd(codec, AC97_REG_POWER, (codec->flags & AC97_F_EAPD_INV)? 0x8000 : 0x0000);

	i = ac97_rdcd(codec, AC97_REG_RESET);
	j = ac97_rdcd(codec, AC97_REG_RESET);
	k = ac97_rdcd(codec, AC97_REG_RESET);
	/*
	 * Let see if this codec can return consistent value.
	 * If not, turn on aggressive read workaround
	 * (STAC9704 comes in mind).
	 */
	if (i != j || j != k) {
		codec->flags |= AC97_F_RDCD_BUG;
		i = ac97_rdcd(codec, AC97_REG_RESET);
	}
	codec->caps = i & 0x03ff;
	codec->se =  (i & 0x7c00) >> 10;

	id = (ac97_rdcd(codec, AC97_REG_ID1) << 16) | ac97_rdcd(codec, AC97_REG_ID2);
	if (id == 0 || id == 0xffffffff) {
		device_printf(codec->dev, "ac97 codec invalid or not present (id == %x)\n", id);
		snd_mtxunlock(codec->lock);
		return ENODEV;
	}

	codec->id = id;
	codec->subvendor = (u_int32_t)pci_get_subdevice(codec->dev) << 16;
	codec->subvendor |= (u_int32_t)pci_get_subvendor(codec->dev) &
	    0x0000ffff;
	codec->noext = 0;
	codec_patch = NULL;

	cname = NULL;
	model = step = 0;
	for (i = 0; ac97codecid[i].id; i++) {
		u_int32_t modelmask = 0xffffffff ^ ac97codecid[i].stepmask;
		if ((ac97codecid[i].id & modelmask) == (id & modelmask)) {
			codec->noext = ac97codecid[i].noext;
			codec_patch = ac97codecid[i].patch;
			cname = ac97codecid[i].name;
			model = (id & modelmask) & 0xff;
			step = (id & ~modelmask) & 0xff;
			break;
		}
	}

	vname = NULL;
	for (i = 0; ac97vendorid[i].id; i++) {
		if (ac97vendorid[i].id == (id & 0xffffff00)) {
			vname = ac97vendorid[i].name;
			break;
		}
	}

	codec->extcaps = 0;
	codec->extid = 0;
	codec->extstat = 0;
	if (!codec->noext) {
		i = ac97_rdcd(codec, AC97_REGEXT_ID);
		if (i != 0xffff) {
			codec->extcaps = i & 0x3fff;
			codec->extid =  (i & 0xc000) >> 14;
			codec->extstat = ac97_rdcd(codec, AC97_REGEXT_STAT) & AC97_EXTCAPS;
		}
	}

	for (i = 0; i < AC97_MIXER_SIZE; i++) {
		codec->mix[i] = ac97mixtable_default[i];
	}
	ac97_fix_auxout(codec);
	ac97_fix_tone(codec);
	if (codec_patch)
		codec_patch(codec);

	for (i = 0; i < AC97_MIXER_SIZE; i++) {
		k = codec->noext? codec->mix[i].enable : 1;
		reg = codec->mix[i].reg;
		if (reg < 0)
			reg = -reg;
		if (k && reg) {
			j = old = ac97_rdcd(codec, reg);
			/*
			 * Test for mute bit (except for AC97_MIX_TONE,
			 * where we simply assume it as available).
			 */
			if (codec->mix[i].mute) {
				ac97_wrcd(codec, reg, j | 0x8000);
				j = ac97_rdcd(codec, reg);
			} else
				j |= 0x8000;
			if ((j & 0x8000)) {
				/*
				 * Test whether the control width should be
				 * 4, 5 or 6 bit. For 5bit register, we should
				 * test it whether it's really 5 or 6bit. Leave
				 * 4bit register alone, because sometimes an
				 * attempt to write past 4th bit may cause
				 * incorrect result especially for AC97_MIX_BEEP
				 * (ac97 2.3).
				 */
				bit = codec->mix[i].bits;
				if (bit == 5)
					bit++;
				j = ((1 << bit) - 1) << codec->mix[i].ofs;
				ac97_wrcd(codec, reg,
					j | (codec->mix[i].mute ? 0x8000 : 0));
				k = ac97_rdcd(codec, reg) & j;
				k >>= codec->mix[i].ofs;
				if (reg == AC97_MIX_TONE &&
							((k & 0x0001) == 0x0000))
					k >>= 1;
				for (j = 0; k >> j; j++)
					;
				if (j != 0) {
#if 0
					device_printf(codec->dev, "%2d: [ac97_rdcd() = %d] [Testbit = %d] %d -> %d\n",
						i, k, bit, codec->mix[i].bits, j);
#endif
					codec->mix[i].enable = 1;
					codec->mix[i].bits = j;
				} else if (reg == AC97_MIX_BEEP) {
					/*
					 * Few codec such as CX20468-21 does
					 * have this control register, although
					 * the only usable part is the mute bit.
					 */
					codec->mix[i].enable = 1;
				} else
					codec->mix[i].enable = 0;
			} else
				codec->mix[i].enable = 0;
			ac97_wrcd(codec, reg, old);
		}
#if 0
		printf("mixch %d, en=%d, b=%d\n", i, codec->mix[i].enable, codec->mix[i].bits);
#endif
	}

	device_printf(codec->dev, "<%s>\n",
		      ac97_hw_desc(codec->id, vname, cname, desc));

	if (bootverbose) {
		if (codec->flags & AC97_F_RDCD_BUG)
			device_printf(codec->dev, "Buggy AC97 Codec: aggressive ac97_rdcd() workaround enabled\n");
		device_printf(codec->dev, "Codec features ");
		for (i = j = 0; i < 10; i++)
			if (codec->caps & (1 << i))
				printf("%s%s", j++? ", " : "", ac97feature[i]);
		printf("%s%d bit master volume", j++? ", " : "", codec->mix[SOUND_MIXER_VOLUME].bits);
		printf("%s%s\n", j? ", " : "", ac97enhancement[codec->se]);

		if (codec->extcaps != 0 || codec->extid) {
			device_printf(codec->dev, "%s codec",
				      codec->extid? "Secondary" : "Primary");
			if (codec->extcaps)
				printf(" extended features ");
			for (i = j = 0; i < 14; i++)
				if (codec->extcaps & (1 << i))
					printf("%s%s", j++? ", " : "", ac97extfeature[i]);
			printf("\n");
		}
	}

	i = 0;
	while ((ac97_rdcd(codec, AC97_REG_POWER) & 2) == 0) {
		if (++i == 100) {
			device_printf(codec->dev, "ac97 codec reports dac not ready\n");
			break;
		}
		DELAY(1000);
	}
	if (bootverbose)
		device_printf(codec->dev, "ac97 codec dac ready count: %d\n", i);
	snd_mtxunlock(codec->lock);
	return 0;
}