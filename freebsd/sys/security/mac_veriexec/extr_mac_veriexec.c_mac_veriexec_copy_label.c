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
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLOT (struct label*) ; 
 int /*<<< orphan*/  SLOT_SET (struct label*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
mac_veriexec_copy_label(struct label *src, struct label *dest)
{

	SLOT_SET(dest, SLOT(src));
}