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
struct m_tag {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_CHECK (int /*<<< orphan*/ ,struct label*,int) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct label*,int) ; 
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct label*) ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  mac_destroy_label (struct label*) ; 
 int /*<<< orphan*/  mac_init_label (struct label*) ; 
 int /*<<< orphan*/  mbuf_destroy_label ; 
 int /*<<< orphan*/  mbuf_init_label ; 

int
mac_mbuf_tag_init(struct m_tag *tag, int flag)
{
	struct label *label;
	int error;

	label = (struct label *) (tag + 1);
	mac_init_label(label);

	if (flag & M_WAITOK)
		MAC_POLICY_CHECK(mbuf_init_label, label, flag);
	else
		MAC_POLICY_CHECK_NOSLEEP(mbuf_init_label, label, flag);
	if (error) {
		MAC_POLICY_PERFORM_NOSLEEP(mbuf_destroy_label, label);
		mac_destroy_label(label);
	}
	return (error);
}