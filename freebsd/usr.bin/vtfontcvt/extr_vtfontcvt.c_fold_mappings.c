#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mapping_list {int dummy; } ;
struct mapping {scalar_t__ m_char; scalar_t__ m_length; TYPE_1__* m_glyph; } ;
struct TYPE_2__ {scalar_t__ g_index; } ;

/* Variables and functions */
 struct mapping* TAILQ_FIRST (struct mapping_list*) ; 
 struct mapping* TAILQ_NEXT (struct mapping*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_list ; 
 int /*<<< orphan*/ * map_folded_count ; 
 struct mapping_list* maps ; 

__attribute__((used)) static void
fold_mappings(unsigned int map_idx)
{
	struct mapping_list *ml = &maps[map_idx];
	struct mapping *mn, *mp, *mbase;

	mp = mbase = TAILQ_FIRST(ml);
	for (mp = mbase = TAILQ_FIRST(ml); mp != NULL; mp = mn) {
		mn = TAILQ_NEXT(mp, m_list);
		if (mn != NULL && mn->m_char == mp->m_char + 1 &&
		    mn->m_glyph->g_index == mp->m_glyph->g_index + 1)
			continue;
		mbase->m_length = mp->m_char - mbase->m_char + 1;
		mbase = mp = mn;
		map_folded_count[map_idx]++;
	}
}