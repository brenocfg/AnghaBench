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
struct tuple_callbacks {char* member_1; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct cis_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CISTPL_GENERIC ; 
 int /*<<< orphan*/  cardbus_build_cis ; 
 int cardbus_parse_cis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuple_callbacks*,struct cis_buffer*) ; 

__attribute__((used)) static int
cardbus_device_buffer_cis(device_t parent, device_t child,
    struct cis_buffer *cbp)
{
	struct tuple_callbacks cb[] = {
		{CISTPL_GENERIC, "GENERIC", cardbus_build_cis}
	};

	return (cardbus_parse_cis(parent, child, cb, cbp));
}