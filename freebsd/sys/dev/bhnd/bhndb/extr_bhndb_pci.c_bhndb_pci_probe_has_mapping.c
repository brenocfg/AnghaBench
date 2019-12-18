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
struct bhndb_pci_probe {scalar_t__ m_target; TYPE_1__* m_win; int /*<<< orphan*/ * m_res; int /*<<< orphan*/  m_valid; } ;
typedef  scalar_t__ bhnd_size_t ;
typedef  scalar_t__ bhnd_addr_t ;
struct TYPE_2__ {scalar_t__ win_type; scalar_t__ win_size; } ;

/* Variables and functions */
 scalar_t__ BHNDB_REGWIN_T_DYN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static bool
bhndb_pci_probe_has_mapping(struct bhndb_pci_probe *probe, bhnd_addr_t addr,
    bhnd_size_t size)
{
	if (!probe->m_valid)
		return (false);

	KASSERT(probe->m_win != NULL, ("missing register window"));
	KASSERT(probe->m_res != NULL, ("missing regwin resource"));
	KASSERT(probe->m_win->win_type == BHNDB_REGWIN_T_DYN,
	    ("unexpected window type %d", probe->m_win->win_type));

	if (addr < probe->m_target)
		return (false);

	if (addr >= probe->m_target + probe->m_win->win_size)
		return (false);

	if ((probe->m_target + probe->m_win->win_size) - addr < size)
		return (false);

	return (true);
}