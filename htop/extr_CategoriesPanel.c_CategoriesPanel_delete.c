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
typedef  int /*<<< orphan*/  Panel ;
typedef  int /*<<< orphan*/  Object ;
typedef  int /*<<< orphan*/  CategoriesPanel ;

/* Variables and functions */
 int /*<<< orphan*/  Panel_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CategoriesPanel_delete(Object* object) {
   Panel* super = (Panel*) object;
   CategoriesPanel* this = (CategoriesPanel*) object;
   Panel_done(super);
   free(this);
}