#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int frow; int fcol; } ;
typedef  TYPE_1__ FIELD ;

/* Variables and functions */
 TYPE_1__* Sorted_Next_Field (TYPE_1__*) ; 
 TYPE_1__* Sorted_Previous_Field (TYPE_1__*) ; 

__attribute__((used)) static FIELD *
Upper_Neighbor_Field(FIELD *field)
{
  FIELD *field_on_page = field;
  int frow = field->frow;
  int fcol = field->fcol;

  /* Walk back to the 'previous' line. The second term in the while clause
     just guarantees that we stop if we cycled through the line because
     there might be no 'previous' line if the page has just one line.
   */
  do
    {
      field_on_page = Sorted_Previous_Field(field_on_page);
    }
  while (field_on_page->frow == frow && field_on_page->fcol != fcol);

  if (field_on_page->frow != frow)
    {
      /* We really found a 'previous' line. We are positioned at the
         rightmost field on this line */
      frow = field_on_page->frow;

      /* We walk to the left as long as we are really right of the
         field. */
      while (field_on_page->frow == frow && field_on_page->fcol > fcol)
	field_on_page = Sorted_Previous_Field(field_on_page);

      /* If we wrapped, just go to the right which is the first field on
         the row */
      if (field_on_page->frow != frow)
	field_on_page = Sorted_Next_Field(field_on_page);
    }

  return (field_on_page);
}