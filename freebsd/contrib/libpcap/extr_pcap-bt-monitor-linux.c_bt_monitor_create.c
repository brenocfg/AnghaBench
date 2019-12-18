#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  activate_op; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERFACE_NAME ; 
 int /*<<< orphan*/  bt_monitor_activate ; 
 TYPE_1__* pcap_create_common (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* strrchr (char const*,char) ; 

pcap_t *
bt_monitor_create(const char *device, char *ebuf, int *is_ours)
{
    pcap_t      *p;
    const char  *cp;

    cp = strrchr(device, '/');
    if (cp == NULL)
        cp = device;

    if (strcmp(cp, INTERFACE_NAME) != 0) {
        *is_ours = 0;
        return NULL;
    }

    *is_ours = 1;
    p = pcap_create_common(ebuf, 0);
    if (p == NULL)
        return NULL;

    p->activate_op = bt_monitor_activate;

    return p;
}