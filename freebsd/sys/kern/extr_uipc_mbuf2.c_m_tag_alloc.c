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
typedef  int /*<<< orphan*/  uint32_t ;
struct m_tag {int /*<<< orphan*/  m_tag_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_CHECKSLEEP (int) ; 
 int /*<<< orphan*/  M_PACKET_TAGS ; 
 int /*<<< orphan*/  m_tag_free_default ; 
 int /*<<< orphan*/  m_tag_setup (struct m_tag*,int /*<<< orphan*/ ,int,int) ; 
 struct m_tag* malloc (int,int /*<<< orphan*/ ,int) ; 

struct m_tag *
m_tag_alloc(uint32_t cookie, int type, int len, int wait)
{
	struct m_tag *t;

	MBUF_CHECKSLEEP(wait);
	if (len < 0)
		return NULL;
	t = malloc(len + sizeof(struct m_tag), M_PACKET_TAGS, wait);
	if (t == NULL)
		return NULL;
	m_tag_setup(t, cookie, type, len);
	t->m_tag_free = m_tag_free_default;
	return t;
}