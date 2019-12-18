#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ind_size; } ;
struct TYPE_3__ {int ind_level; scalar_t__ pcase; } ;

/* Variables and functions */
 int case_ind ; 
 int label_offset ; 
 TYPE_2__ opt ; 
 TYPE_1__ ps ; 
 char* s_lab ; 

int
compute_label_target(void)
{
    return
	ps.pcase ? (int) (case_ind * opt.ind_size) + 1
	: *s_lab == '#' ? 1
	: opt.ind_size * (ps.ind_level - label_offset) + 1;
}