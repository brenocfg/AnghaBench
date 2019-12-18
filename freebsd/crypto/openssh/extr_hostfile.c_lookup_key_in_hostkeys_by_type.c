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
struct hostkeys {int dummy; } ;
struct hostkey_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ HOST_FOUND ; 
 scalar_t__ check_hostkeys_by_key_or_type (struct hostkeys*,int /*<<< orphan*/ *,int,struct hostkey_entry const**) ; 

int
lookup_key_in_hostkeys_by_type(struct hostkeys *hostkeys, int keytype,
    const struct hostkey_entry **found)
{
	return (check_hostkeys_by_key_or_type(hostkeys, NULL, keytype,
	    found) == HOST_FOUND);
}