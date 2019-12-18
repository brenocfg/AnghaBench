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
typedef  int /*<<< orphan*/  u_int32_t ;
struct fw_eui64 {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct eui64 {int /*<<< orphan*/ * octet; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fweui2eui64(const struct fw_eui64 *fweui, struct eui64 *eui)
{
	*(u_int32_t*)&(eui->octet[0]) = htonl(fweui->hi);
	*(u_int32_t*)&(eui->octet[4]) = htonl(fweui->lo);
}