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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * currcfg; } ;
struct TYPE_3__ {void* currextra; void* currep; void* currifc; void* currifcw; struct usb_config_descriptor* currcfg; } ;
struct usb_parse_state {int preparse; TYPE_2__ a; TYPE_1__ b; } ;
struct usb_config_descriptor {int dummy; } ;
typedef  int /*<<< orphan*/  ps ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libusb20_parse_config_desc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (struct usb_parse_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_parse_config (struct usb_parse_state*) ; 

int
usb_parse_configuration(struct usb_config_descriptor *config,
    uint8_t *buffer)
{
	struct usb_parse_state ps;
	uint8_t *ptr;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;

	if ((buffer == NULL) || (config == NULL)) {
		return (-1);
	}
	memset(&ps, 0, sizeof(ps));

	ps.a.currcfg = libusb20_parse_config_desc(buffer);
	ps.b.currcfg = config;
	if (ps.a.currcfg == NULL) {
		/* could not parse config or out of memory */
		return (-1);
	}
	/* do the pre-parse */
	ps.preparse = 1;
	usb_parse_config(&ps);

	a = ((uint8_t *)(ps.b.currifcw) - ((uint8_t *)0));
	b = ((uint8_t *)(ps.b.currifc) - ((uint8_t *)0));
	c = ((uint8_t *)(ps.b.currep) - ((uint8_t *)0));
	d = ((uint8_t *)(ps.b.currextra) - ((uint8_t *)0));

	/* allocate memory for our configuration */
	ptr = malloc(a + b + c + d);
	if (ptr == NULL) {
		/* free config structure */
		free(ps.a.currcfg);
		return (-1);
	}

	/* "currifcw" must be first, hence this pointer is freed */
	ps.b.currifcw = (void *)(ptr);
	ps.b.currifc = (void *)(ptr + a);
	ps.b.currep = (void *)(ptr + a + b);
	ps.b.currextra = (void *)(ptr + a + b + c);

	/* generate a libusb v0.1 compatible structure */
	ps.preparse = 0;
	usb_parse_config(&ps);

	/* free config structure */
	free(ps.a.currcfg);

	return (0);			/* success */
}