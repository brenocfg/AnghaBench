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
struct torus {struct t_switch**** sw; } ;
struct t_switch {int i; int j; int k; } ;
struct f_switch {int dummy; } ;

/* Variables and functions */
 struct t_switch* alloc_tswitch (struct torus*,struct f_switch*) ; 

__attribute__((used)) static
bool install_tswitch(struct torus *t,
		     int i, int j, int k, struct f_switch *fsw)
{
	struct t_switch **sw = &t->sw[i][j][k];

	if (!*sw)
		*sw = alloc_tswitch(t, fsw);

	if (*sw) {
		(*sw)->i = i;
		(*sw)->j = j;
		(*sw)->k = k;
	}
	return !!*sw;
}