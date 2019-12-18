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
typedef  int /*<<< orphan*/  u8 ;
struct cont_desc {int dummy; } ;

/* Variables and functions */
 size_t parse_container (int /*<<< orphan*/ *,size_t,struct cont_desc*) ; 

__attribute__((used)) static void scan_containers(u8 *ucode, size_t size, struct cont_desc *desc)
{
	while (size) {
		size_t s = parse_container(ucode, size, desc);
		if (!s)
			return;

		/* catch wraparound */
		if (size >= s) {
			ucode += s;
			size  -= s;
		} else {
			return;
		}
	}
}