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
typedef  int /*<<< orphan*/  GSLList ;
typedef  int /*<<< orphan*/  GColors ;

/* Variables and functions */
 int /*<<< orphan*/ * color_list ; 
 int /*<<< orphan*/  find_color_in_list ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_insert_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prepend_color (GColors ** color)
{
  GSLList *match = NULL;

  /* create a list of colors if one does not exist */
  if (color_list == NULL) {
    color_list = list_create (*color);
  }
  /* attempt to find the given color data type (by item and attributes) in
   * our color list */
  else if ((match = list_find (color_list, find_color_in_list, *color))) {
    /* if found, free the recently malloc'd color data type and use
     * existing color */
    free (*color);
    *color = NULL;
  } else {
    /* not a dup, so insert the new color in our color list */
    color_list = list_insert_prepend (color_list, *color);
  }
}