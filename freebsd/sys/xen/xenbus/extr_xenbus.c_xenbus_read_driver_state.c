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
typedef  int /*<<< orphan*/  XenbusState ;

/* Variables and functions */
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  XenbusStateClosed ; 
 int xs_gather (int /*<<< orphan*/ ,char const*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

XenbusState
xenbus_read_driver_state(const char *path)
{
        XenbusState result;
        int error;

        error = xs_gather(XST_NIL, path, "state", "%d", &result, NULL);
        if (error)
                result = XenbusStateClosed;

        return (result);
}