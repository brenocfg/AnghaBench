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
 int /*<<< orphan*/  fatal_exit (char*) ; 

__attribute__((used)) static void
sodium_misuse_handler(void)
{
	fatal_exit(
		"dnscrypt: libsodium could not be initialized, this typically"
		" happens when no good source of entropy is found. If you run"
		" unbound in a chroot, make sure /dev/random is available. See"
		" https://www.unbound.net/documentation/unbound.conf.html");
}