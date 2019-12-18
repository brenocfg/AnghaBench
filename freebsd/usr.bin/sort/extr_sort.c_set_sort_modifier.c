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
struct sort_mods {int bflag; int dflag; int fflag; int gflag; int iflag; int Rflag; int Mflag; int nflag; int rflag; int Vflag; int hflag; int /*<<< orphan*/  func; } ;
struct TYPE_2__ {int complex_sort; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_sort_func (struct sort_mods*) ; 
 int /*<<< orphan*/  initialise_months () ; 
 int need_hint ; 
 int need_random ; 
 int print_symbols_on_debug ; 
 TYPE_1__ sort_opts_vals ; 

__attribute__((used)) static bool
set_sort_modifier(struct sort_mods *sm, int c)
{

	if (sm == NULL)
		return (true);

	switch (c){
	case 'b':
		sm->bflag = true;
		break;
	case 'd':
		sm->dflag = true;
		break;
	case 'f':
		sm->fflag = true;
		break;
	case 'g':
		sm->gflag = true;
		need_hint = true;
		break;
	case 'i':
		sm->iflag = true;
		break;
	case 'R':
		sm->Rflag = true;
		need_hint = true;
		need_random = true;
		break;
	case 'M':
		initialise_months();
		sm->Mflag = true;
		need_hint = true;
		break;
	case 'n':
		sm->nflag = true;
		need_hint = true;
		print_symbols_on_debug = true;
		break;
	case 'r':
		sm->rflag = true;
		break;
	case 'V':
		sm->Vflag = true;
		break;
	case 'h':
		sm->hflag = true;
		need_hint = true;
		print_symbols_on_debug = true;
		break;
	default:
		return (false);
	}

	sort_opts_vals.complex_sort = true;
	sm->func = get_sort_func(sm);
	return (true);
}