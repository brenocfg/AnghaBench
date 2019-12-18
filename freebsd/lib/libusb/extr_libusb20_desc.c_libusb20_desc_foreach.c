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
struct libusb20_me_struct {int /*<<< orphan*/  len; scalar_t__ ptr; } ;

/* Variables and functions */
 int* LIBUSB20_ADD_BYTES (int const*,int /*<<< orphan*/ ) ; 

const uint8_t *
libusb20_desc_foreach(const struct libusb20_me_struct *pdesc,
    const uint8_t *psubdesc)
{
	const uint8_t *start;
	const uint8_t *end;
	const uint8_t *desc_next;

	/* be NULL safe */
	if (pdesc == NULL)
		return (NULL);

	start = (const uint8_t *)pdesc->ptr;
	end = LIBUSB20_ADD_BYTES(start, pdesc->len);

	/* get start of next descriptor */
	if (psubdesc == NULL)
		psubdesc = start;
	else
		psubdesc = psubdesc + psubdesc[0];

	/* check that the next USB descriptor is within the range */
	if ((psubdesc < start) || (psubdesc >= end))
		return (NULL);		/* out of range, or EOD */

	/* check start of the second next USB descriptor, if any */
	desc_next = psubdesc + psubdesc[0];
	if ((desc_next < start) || (desc_next > end))
		return (NULL);		/* out of range */

	/* check minimum descriptor length */
	if (psubdesc[0] < 3)
		return (NULL);		/* too short descriptor */

	return (psubdesc);		/* return start of next descriptor */
}