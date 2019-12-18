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
struct TYPE_2__ {void* ifru_data; } ;
struct ifreq {TYPE_1__ ifr_ifru; int /*<<< orphan*/  ifr_name; } ;
typedef  scalar_t__ mac_t ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIFMAC ; 
 int /*<<< orphan*/  free (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  mac_free (scalar_t__) ; 
 int mac_prepare_ifnet_label (scalar_t__*) ; 
 int mac_to_text (scalar_t__,char**) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
maclabel_status(int s)
{
	struct ifreq ifr;
	mac_t label;
	char *label_text;

	memset(&ifr, 0, sizeof(ifr));
	strlcpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));

	if (mac_prepare_ifnet_label(&label) == -1)
		return;
	ifr.ifr_ifru.ifru_data = (void *)label;
	if (ioctl(s, SIOCGIFMAC, &ifr) == -1)
		goto mac_free;

	
	if (mac_to_text(label, &label_text) == -1)
		goto mac_free;

	if (strlen(label_text) != 0)
		printf("\tmaclabel %s\n", label_text);
	free(label_text);

mac_free:
	mac_free(label);
}