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
struct TYPE_3__ {scalar_t__ n_strx; } ;
struct TYPE_4__ {TYPE_1__ n_un; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char const* str_base ; 
 TYPE_2__* sym_base ; 
 unsigned long sym_count ; 

__attribute__((used)) static const char *
sym_name(unsigned long n)
{
    assert(n < sym_count);
    if (sym_base[n].n_un.n_strx == 0)
	return "";
    return str_base + sym_base[n].n_un.n_strx;
}