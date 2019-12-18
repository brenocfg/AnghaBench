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
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_INIT (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_SYSV_MSG ; 
 int /*<<< orphan*/  sysvmsg_init_label ; 

__attribute__((used)) static void
test_sysvmsg_init_label(struct label *label)
{
	LABEL_INIT(label, MAGIC_SYSV_MSG);
	COUNTER_INC(sysvmsg_init_label);
}