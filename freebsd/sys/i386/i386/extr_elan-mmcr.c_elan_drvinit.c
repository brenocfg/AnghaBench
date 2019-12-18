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

/* Variables and functions */
 int BIOS_OEM_MAXLEN ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ bios_oem_strings (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bios_soekris ; 
 int /*<<< orphan*/  elan_cdevsw ; 
 int /*<<< orphan*/  elan_watchdog ; 
 int /*<<< orphan*/  gpio_config ; 
 int /*<<< orphan*/  gpio_led ; 
 int* led_cookie ; 
 int /*<<< orphan*/  led_create (int /*<<< orphan*/ ,int*,char*) ; 
 int /*<<< orphan*/ * led_dev ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * mmcrptr ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  watchdog_list ; 

__attribute__((used)) static void
elan_drvinit(void)
{

#ifdef CPU_SOEKRIS
#define BIOS_OEM_MAXLEN 72
        static u_char bios_oem[BIOS_OEM_MAXLEN] = "\0";
#endif /* CPU_SOEKRIS */

	/* If no elan found, just return */
	if (mmcrptr == NULL)
		return;

	printf("Elan-mmcr driver: MMCR at %p.%s\n", 
	    mmcrptr,
#ifdef CPU_ELAN_PPS
	    " PPS support."
#else
	    ""
#endif
	    );

	make_dev(&elan_cdevsw, 0,
	    UID_ROOT, GID_WHEEL, 0600, "elan-mmcr");

#ifdef CPU_SOEKRIS
	if ( bios_oem_strings(&bios_soekris, bios_oem, BIOS_OEM_MAXLEN) > 0 )
		printf("Elan-mmcr %s\n", bios_oem);

	/* Create the error LED on GPIO9 */
	led_cookie[9] = 0x02000c34;
	led_dev[9] = led_create(gpio_led, &led_cookie[9], "error");
	
	/* Disable the unavailable GPIO pins */
	strcpy(gpio_config, "-----....--..--------..---------");
#else /* !CPU_SOEKRIS */
	/* We don't know which pins are available so enable them all */
	strcpy(gpio_config, "................................");
#endif /* CPU_SOEKRIS */

	EVENTHANDLER_REGISTER(watchdog_list, elan_watchdog, NULL, 0);
}