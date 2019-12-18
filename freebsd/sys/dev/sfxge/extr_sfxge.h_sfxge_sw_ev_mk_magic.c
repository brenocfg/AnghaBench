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
typedef  unsigned int uint16_t ;
typedef  enum sfxge_sw_ev { ____Placeholder_sfxge_sw_ev } sfxge_sw_ev ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 unsigned int SFXGE_MAGIC_DMAQ_LABEL_MASK ; 
 unsigned int SFXGE_SW_EV_MAGIC (int) ; 

__attribute__((used)) static inline uint16_t
sfxge_sw_ev_mk_magic(enum sfxge_sw_ev sw_ev, unsigned int label)
{
	KASSERT((label & SFXGE_MAGIC_DMAQ_LABEL_MASK) == label,
	    ("(label & SFXGE_MAGIC_DMAQ_LABEL_MASK) != label"));
	return SFXGE_SW_EV_MAGIC(sw_ev) | label;
}