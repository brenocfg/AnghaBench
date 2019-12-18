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
 int ENOMEM ; 
 int MPC_OBJECT_MBUF ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int /*<<< orphan*/  PACKET_TAG_MACLABEL ; 
 int /*<<< orphan*/  m_tag_free (struct m_tag*) ; 
 struct m_tag* m_tag_get (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 
 int mac_labeled ; 
 int mac_mbuf_tag_init (struct m_tag*,int) ; 

int
mac_mbuf_init(struct mbuf *m, int flag)
{
	struct m_tag *tag;
	int error;

	M_ASSERTPKTHDR(m);

	if (mac_labeled & MPC_OBJECT_MBUF) {
		tag = m_tag_get(PACKET_TAG_MACLABEL, sizeof(struct label),
		    flag);
		if (tag == NULL)
			return (ENOMEM);
		error = mac_mbuf_tag_init(tag, flag);
		if (error) {
			m_tag_free(tag);
			return (error);
		}
		m_tag_prepend(m, tag);
	}
	return (0);
}