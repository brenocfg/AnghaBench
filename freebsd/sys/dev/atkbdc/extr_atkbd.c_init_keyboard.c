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
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 scalar_t__ ALLOW_DISABLE_KBD (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HAS_QUIRK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBDC_DISABLE_KBD_PORT ; 
 int /*<<< orphan*/  KBDC_ENABLE_KBD ; 
 int /*<<< orphan*/  KBDC_QUIRK_RESET_AFTER_PROBE ; 
 int /*<<< orphan*/  KBDC_QUIRK_SETLEDS_ON_INIT ; 
 int /*<<< orphan*/  KBDC_SET_LEDS ; 
 int /*<<< orphan*/  KBDC_SET_SCANCODE_SET ; 
 scalar_t__ KBD_ACK ; 
 int KBD_ENABLE_KBD_INT ; 
 int KBD_ENABLE_KBD_PORT ; 
 int KBD_KBD_CONTROL_BITS ; 
 int KBD_OVERRIDE_KBD_LOCK ; 
 int KBD_TRANSLATION ; 
 int KB_101 ; 
 int KB_84 ; 
 int KB_CONF_ALT_SCANCODESET ; 
 int KB_OTHER ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ atkbd_reset (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int get_controller_command_byte (int /*<<< orphan*/ ) ; 
 int get_kbd_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_kbd_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_kbd_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ send_kbd_command_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ setup_kbd_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_controller_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_keyboard(KBDC kbdc, int *type, int flags)
{
	int codeset;
	int id;
	int c;

	if (!kbdc_lock(kbdc, TRUE)) {
		/* driver error? */
		return EIO;
	}

	/* temporarily block data transmission from the keyboard */
	write_controller_command(kbdc, KBDC_DISABLE_KBD_PORT);

	/* save the current controller command byte */
	empty_both_buffers(kbdc, 200);
	c = get_controller_command_byte(kbdc);
	if (c == -1) {
		/* CONTROLLER ERROR */
		kbdc_lock(kbdc, FALSE);
		printf("atkbd: unable to get the current command byte value.\n");
		return EIO;
	}
	if (bootverbose)
		printf("atkbd: the current kbd controller command byte %04x\n",
		   c);
#if 0
	/* override the keyboard lock switch */
	c |= KBD_OVERRIDE_KBD_LOCK;
#endif

	/* enable the keyboard port, but disable the keyboard intr. */
	if (setup_kbd_port(kbdc, TRUE, FALSE)) {
		/* CONTROLLER ERROR: there is very little we can do... */
		printf("atkbd: unable to set the command byte.\n");
		kbdc_lock(kbdc, FALSE);
		return EIO;
	}

	if (HAS_QUIRK(kbdc, KBDC_QUIRK_RESET_AFTER_PROBE) &&
	    atkbd_reset(kbdc, flags, c)) {
		kbdc_lock(kbdc, FALSE);
		return EIO;
	}

	/* 
	 * Check if we have an XT keyboard before we attempt to reset it. 
	 * The procedure assumes that the keyboard and the controller have 
	 * been set up properly by BIOS and have not been messed up 
	 * during the boot process.
	 */
	codeset = -1;
	if (flags & KB_CONF_ALT_SCANCODESET)
		/* the user says there is a XT keyboard */
		codeset = 1;
#ifdef KBD_DETECT_XT_KEYBOARD
	else if ((c & KBD_TRANSLATION) == 0) {
		/* SET_SCANCODE_SET is not always supported; ignore error */
		if (send_kbd_command_and_data(kbdc, KBDC_SET_SCANCODE_SET, 0)
			== KBD_ACK) 
			codeset = read_kbd_data(kbdc);
	}
	if (bootverbose)
		printf("atkbd: scancode set %d\n", codeset);
#endif /* KBD_DETECT_XT_KEYBOARD */
 
	*type = KB_OTHER;
	id = get_kbd_id(kbdc);
	switch(id) {
	case 0x41ab:	/* 101/102/... Enhanced */
	case 0x83ab:	/* ditto */
	case 0x54ab:	/* SpaceSaver */
	case 0x84ab:	/* ditto */
#if 0
	case 0x90ab:	/* 'G' */
	case 0x91ab:	/* 'P' */
	case 0x92ab:	/* 'A' */
#endif
		*type = KB_101;
		break;
	case -1:	/* AT 84 keyboard doesn't return ID */
		*type = KB_84;
		break;
	default:
		break;
	}
	if (bootverbose)
		printf("atkbd: keyboard ID 0x%x (%d)\n", id, *type);

	if (!HAS_QUIRK(kbdc, KBDC_QUIRK_RESET_AFTER_PROBE) &&
	    atkbd_reset(kbdc, flags, c)) {
		kbdc_lock(kbdc, FALSE);
		return EIO;
	}

	/*
	 * Allow us to set the XT_KEYBD flag so that keyboards
	 * such as those on the IBM ThinkPad laptop computers can be used
	 * with the standard console driver.
	 */
	if (codeset == 1) {
		if (send_kbd_command_and_data(kbdc,
			KBDC_SET_SCANCODE_SET, codeset) == KBD_ACK) {
			/* XT kbd doesn't need scan code translation */
			c &= ~KBD_TRANSLATION;
		} else {
			/*
			 * KEYBOARD ERROR 
			 * The XT kbd isn't usable unless the proper scan
			 * code set is selected. 
			 */
			set_controller_command_byte(kbdc, ALLOW_DISABLE_KBD(kbdc)
			    ? 0xff : KBD_KBD_CONTROL_BITS, c);
			kbdc_lock(kbdc, FALSE);
			printf("atkbd: unable to set the XT keyboard mode.\n");
			return EIO;
		}
	}

#if defined(__sparc64__)
	if (send_kbd_command_and_data(
		kbdc, KBDC_SET_SCANCODE_SET, 2) != KBD_ACK) {
		printf("atkbd: can't set translation.\n");
	}
	c |= KBD_TRANSLATION;
#endif

	/*
	 * Some keyboards require a SETLEDS command to be sent after
	 * the reset command before they will send keystrokes to us
	 */
	if (HAS_QUIRK(kbdc, KBDC_QUIRK_SETLEDS_ON_INIT) &&
	    send_kbd_command_and_data(kbdc, KBDC_SET_LEDS, 0) != KBD_ACK) {
		printf("atkbd: setleds failed\n");
	}
	if (!ALLOW_DISABLE_KBD(kbdc))
	    send_kbd_command(kbdc, KBDC_ENABLE_KBD);

	/* enable the keyboard port and intr. */
	if (!set_controller_command_byte(kbdc, 
		KBD_KBD_CONTROL_BITS | KBD_TRANSLATION | KBD_OVERRIDE_KBD_LOCK,
		(c & (KBD_TRANSLATION | KBD_OVERRIDE_KBD_LOCK))
		    | KBD_ENABLE_KBD_PORT | KBD_ENABLE_KBD_INT)) {
		/*
		 * CONTROLLER ERROR 
		 * This is serious; we are left with the disabled
		 * keyboard intr. 
		 */
		set_controller_command_byte(kbdc, ALLOW_DISABLE_KBD(kbdc)
		    ? 0xff : (KBD_KBD_CONTROL_BITS | KBD_TRANSLATION |
			KBD_OVERRIDE_KBD_LOCK), c);
		kbdc_lock(kbdc, FALSE);
		printf("atkbd: unable to enable the keyboard port and intr.\n");
		return EIO;
	}

	kbdc_lock(kbdc, FALSE);
	return 0;
}