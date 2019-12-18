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
struct m_tag {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_TAG_MACLABEL ; 
 struct m_tag* m_tag_find (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct label *
mac_mbuf_to_label(struct mbuf *m)
{
	struct m_tag *tag;
	struct label *label;

	if (m == NULL)
		return (NULL);
	tag = m_tag_find(m, PACKET_TAG_MACLABEL, NULL);
	if (tag == NULL)
		return (NULL);
	label = (struct label *)(tag+1);
	return (label);
}