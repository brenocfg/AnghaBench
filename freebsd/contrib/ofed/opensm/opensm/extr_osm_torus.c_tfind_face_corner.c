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
struct t_switch {int /*<<< orphan*/  tmp; } ;
struct f_switch {int dummy; } ;

/* Variables and functions */
 struct f_switch* ffind_face_corner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
struct f_switch *tfind_face_corner(struct t_switch *tsw0,
				   struct t_switch *tsw1,
				   struct t_switch *tsw2)
{
	if (!(tsw0 && tsw1 && tsw2))
		return NULL;

	return ffind_face_corner(tsw0->tmp, tsw1->tmp, tsw2->tmp);
}