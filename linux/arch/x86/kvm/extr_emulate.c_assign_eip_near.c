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
typedef  int /*<<< orphan*/  ulong ;
struct x86_emulate_ctxt {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int assign_eip (struct x86_emulate_ctxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int assign_eip_near(struct x86_emulate_ctxt *ctxt, ulong dst)
{
	return assign_eip(ctxt, dst, ctxt->mode);
}