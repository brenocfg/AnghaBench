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
typedef  char u_char ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BIOS_OEM_MAXLEN ; 
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advantech_watchdog ; 
 int /*<<< orphan*/  bios_advantech ; 
 int /*<<< orphan*/  bios_oem_strings (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bios_pcengines ; 
 int /*<<< orphan*/  bios_pcengines_55 ; 
 int /*<<< orphan*/  bios_soekris ; 
 int /*<<< orphan*/  bios_soekris_55 ; 
 int /*<<< orphan*/  bootverbose ; 
 int cba ; 
 int /*<<< orphan*/  cs5536_led_func (int*,int) ; 
 int /*<<< orphan*/  cs5536_watchdog ; 
 int /*<<< orphan*/  geode_counter ; 
 int /*<<< orphan*/  geode_cputicks ; 
 int /*<<< orphan*/  geode_timecounter ; 
 int /*<<< orphan*/  geode_watchdog ; 
 int gpio ; 
 int inb (int /*<<< orphan*/ ) ; 
 void* led1 ; 
 int led1b ; 
 void* led2 ; 
 int led2b ; 
 void* led3 ; 
 int led3b ; 
 void* led_create (int /*<<< orphan*/  (*) (int*,int),int*,char*) ; 
 int /*<<< orphan*/  led_func (int*,int) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* rdmsr (int) ; 
 int /*<<< orphan*/  set_cputicker (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static int
geode_probe(device_t self)
{
#define BIOS_OEM_MAXLEN 80
	static u_char bios_oem[BIOS_OEM_MAXLEN] = "\0";

	switch (pci_get_devid(self)) {
	case 0x0515100b:
		if (geode_counter == 0) {
			/*
			 * The address of the CBA is written to this register
			 * by the bios, see p161 in data sheet.
			 */
			cba = pci_read_config(self, 0x64, 4);
			if (bootverbose)
				printf("Geode CBA@ 0x%x\n", cba);
			geode_counter = cba + 0x08;
			outl(cba + 0x0d, 2);
			if (bootverbose)
				printf("Geode rev: %02x %02x\n",
					inb(cba + 0x3c), inb(cba + 0x3d));
			tc_init(&geode_timecounter);
			EVENTHANDLER_REGISTER(watchdog_list, geode_watchdog,
			    NULL, 0);
			set_cputicker(geode_cputicks, 27000000, 0);
		}
		break;
	case 0x0510100b:
		gpio = pci_read_config(self, PCIR_BAR(0), 4);
		gpio &= ~0x1f;
		if (bootverbose)
			printf("Geode GPIO@ = %x\n", gpio);
		if (bios_oem_strings(&bios_soekris,
		    bios_oem, sizeof bios_oem) > 0 ) {
			led1b = 20;
			led1 = led_create(led_func, &led1b, "error");
		} else if (bios_oem_strings(&bios_pcengines,
		    bios_oem, sizeof bios_oem) > 0 ) {
			led1b = -2;
			led2b = -3;
			led3b = -18;
			led1 = led_create(led_func, &led1b, "led1");
			led2 = led_create(led_func, &led2b, "led2");
			led3 = led_create(led_func, &led3b, "led3");
			/*
		 	* Turn on first LED so we don't make
			* people think their box just died.
		 	*/
			led_func(&led1b, 1);
		}
		if (*bios_oem)
			printf("Geode %s\n", bios_oem);
		break;
	case 0x01011078:
		if (bios_oem_strings(&bios_advantech,
		    bios_oem, sizeof bios_oem) > 0 ) {
			printf("Geode %s\n", bios_oem);
			EVENTHANDLER_REGISTER(watchdog_list, advantech_watchdog,
			    NULL, 0);
		}
		break;
	case 0x20801022:
		if (bios_oem_strings(&bios_soekris_55,
		    bios_oem, sizeof bios_oem) > 0 ) {
			led1b = 6;
			led1 = led_create(cs5536_led_func, &led1b, "error");
		} else if (bios_oem_strings(&bios_pcengines_55,
		    bios_oem, sizeof bios_oem) > 0 ) {
			led1b = -6;
			led2b = -25;
			led3b = -27;
			led1 = led_create(cs5536_led_func, &led1b, "led1");
			led2 = led_create(cs5536_led_func, &led2b, "led2");
			led3 = led_create(cs5536_led_func, &led3b, "led3");
			/*
		 	* Turn on first LED so we don't make
			* people think their box just died.
		 	*/
			cs5536_led_func(&led1b, 1);
		}
		if (*bios_oem)
			printf("Geode LX: %s\n", bios_oem);
		if (bootverbose)
			printf("MFGPT bar: %jx\n", rdmsr(0x5140000d));
		EVENTHANDLER_REGISTER(watchdog_list, cs5536_watchdog, NULL, 0);
		break;
	}
	return (ENXIO);
}