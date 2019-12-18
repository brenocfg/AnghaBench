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
struct dbm_macro {void* pp; void* value; } ;
typedef  size_t int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  pages; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 size_t MACRO_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 void* dbm_get (int /*<<< orphan*/ ) ; 
 TYPE_1__** macros ; 
 size_t* nvals ; 

struct dbm_macro *
dbm_macro_get(int32_t im, int32_t iv)
{
	static struct dbm_macro macro;

	assert(im >= 0);
	assert(im < MACRO_MAX);
	assert(iv >= 0);
	assert(iv < nvals[im]);
	macro.value = dbm_get(macros[im][iv].value);
	macro.pp = dbm_get(macros[im][iv].pages);
	return &macro;
}