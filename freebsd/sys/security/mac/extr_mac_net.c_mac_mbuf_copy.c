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
struct mbuf {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct label*,struct label*) ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 
 scalar_t__ mac_policy_count ; 
 int /*<<< orphan*/  mbuf_copy_label ; 

void
mac_mbuf_copy(struct mbuf *m_from, struct mbuf *m_to)
{
	struct label *src_label, *dest_label;

	if (mac_policy_count == 0)
		return;

	src_label = mac_mbuf_to_label(m_from);
	dest_label = mac_mbuf_to_label(m_to);

	MAC_POLICY_PERFORM_NOSLEEP(mbuf_copy_label, src_label, dest_label);
}