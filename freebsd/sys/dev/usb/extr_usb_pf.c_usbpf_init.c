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
 int /*<<< orphan*/  if_clone_advanced (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbpf_clone_create ; 
 int /*<<< orphan*/  usbpf_clone_destroy ; 
 int /*<<< orphan*/  usbpf_clone_match ; 
 int /*<<< orphan*/  usbpf_cloner ; 
 int /*<<< orphan*/  usbusname ; 

__attribute__((used)) static void
usbpf_init(void *arg)
{

	usbpf_cloner = if_clone_advanced(usbusname, 0, usbpf_clone_match,
	    usbpf_clone_create, usbpf_clone_destroy);
}