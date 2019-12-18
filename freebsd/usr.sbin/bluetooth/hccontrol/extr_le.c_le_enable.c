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

/* Variables and functions */
 int NG_HCI_EVENT_MASK_DEFAULT ; 
 int NG_HCI_EVENT_MASK_LE ; 
 int /*<<< orphan*/  NG_HCI_LE_EVENT_MASK_ALL ; 
 int OK ; 
 int USAGE ; 
 int /*<<< orphan*/  set_event_mask (int,int) ; 
 int /*<<< orphan*/  set_le_event_mask (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static
int le_enable(int s, int argc, char *argv[])
{
	if (argc != 1)
		return USAGE;
	
	if (strcasecmp(argv[0], "enable") == 0) {
		set_event_mask(s, NG_HCI_EVENT_MASK_DEFAULT |
			       NG_HCI_EVENT_MASK_LE);
		set_le_event_mask(s, NG_HCI_LE_EVENT_MASK_ALL);
	} else if (strcasecmp(argv[0], "disble") == 0)
		set_event_mask(s, NG_HCI_EVENT_MASK_DEFAULT);
	else
		return USAGE;

	return OK;
}