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
typedef  int uint8_t ;
struct usb_descriptor {int dummy; } ;
struct usb_config_descriptor {int /*<<< orphan*/  wTotalLength; } ;

/* Variables and functions */
 int UGETW (int /*<<< orphan*/ ) ; 

struct usb_descriptor *
usb_desc_foreach(struct usb_config_descriptor *cd, 
    struct usb_descriptor *_desc)
{
	uint8_t *desc_next;
	uint8_t *start;
	uint8_t *end;
	uint8_t *desc;

	/* be NULL safe */
	if (cd == NULL)
		return (NULL);

	/* We assume that the "wTotalLength" has been checked. */
	start = (uint8_t *)cd;
	end = start + UGETW(cd->wTotalLength);
	desc = (uint8_t *)_desc;

	/* Get start of next USB descriptor. */
	if (desc == NULL)
		desc = start;
	else
		desc = desc + desc[0];

	/* Check that the next USB descriptor is within the range. */
	if ((desc < start) || (desc >= end))
		return (NULL);		/* out of range, or EOD */

	/* Check that the second next USB descriptor is within range. */
	desc_next = desc + desc[0];
	if ((desc_next < start) || (desc_next > end))
		return (NULL);		/* out of range */

	/* Check minimum descriptor length. */
	if (desc[0] < 3)
		return (NULL);		/* too short descriptor */

	/* Return start of next descriptor. */
	return ((struct usb_descriptor *)desc);
}