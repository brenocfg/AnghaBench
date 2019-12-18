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
 int /*<<< orphan*/  LABEL_DESTROY (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_MBUF ; 
 int /*<<< orphan*/  mbuf_destroy_label ; 

__attribute__((used)) static void
test_mbuf_destroy_label(struct label *label)
{

	/*
	 * If we're loaded dynamically, there may be mbufs in flight that
	 * didn't have label storage allocated for them.  Handle this
	 * gracefully.
	 */
	if (label == NULL)
		return;

	LABEL_DESTROY(label, MAGIC_MBUF);
	COUNTER_INC(mbuf_destroy_label);
}