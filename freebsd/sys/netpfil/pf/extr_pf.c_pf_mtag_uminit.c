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
struct pf_mtag {int dummy; } ;
struct m_tag {int m_tag_len; int /*<<< orphan*/  m_tag_free; int /*<<< orphan*/  m_tag_id; int /*<<< orphan*/  m_tag_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTAG_ABI_COMPAT ; 
 int /*<<< orphan*/  PACKET_TAG_PF ; 
 int /*<<< orphan*/  pf_mtag_free ; 

__attribute__((used)) static int
pf_mtag_uminit(void *mem, int size, int how)
{
	struct m_tag *t;

	t = (struct m_tag *)mem;
	t->m_tag_cookie = MTAG_ABI_COMPAT;
	t->m_tag_id = PACKET_TAG_PF;
	t->m_tag_len = sizeof(struct pf_mtag);
	t->m_tag_free = pf_mtag_free;

	return (0);
}