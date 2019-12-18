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
struct m_tag {scalar_t__ m_tag_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PACKET_TAGS ; 
 scalar_t__ PACKET_TAG_MACLABEL ; 
 int /*<<< orphan*/  free (struct m_tag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_mbuf_tag_destroy (struct m_tag*) ; 

void
m_tag_free_default(struct m_tag *t)
{
#ifdef MAC
	if (t->m_tag_id == PACKET_TAG_MACLABEL)
		mac_mbuf_tag_destroy(t);
#endif
	free(t, M_PACKET_TAGS);
}