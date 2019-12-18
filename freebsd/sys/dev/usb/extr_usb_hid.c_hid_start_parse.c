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
typedef  int usb_size_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct hid_data {int kindset; int /*<<< orphan*/  const* end; void const* p; void const* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct hid_data* malloc (int,int /*<<< orphan*/ ,int) ; 

struct hid_data *
hid_start_parse(const void *d, usb_size_t len, int kindset)
{
	struct hid_data *s;

	if ((kindset-1) & kindset) {
		DPRINTFN(0, "Only one bit can be "
		    "set in the kindset\n");
		return (NULL);
	}

	s = malloc(sizeof *s, M_TEMP, M_WAITOK | M_ZERO);
	s->start = s->p = d;
	s->end = ((const uint8_t *)d) + len;
	s->kindset = kindset;
	return (s);
}