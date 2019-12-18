#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int frow; int rows; int fcol; int cols; } ;
typedef  TYPE_1__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_FIELD ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 

__attribute__((used)) static int
Field_encloses(FIELD *field, int ry, int rx)
{
  T((T_CALLED("Field_encloses(%p)"), (void *)field));
  if (field != 0
      && field->frow <= ry
      && (field->frow + field->rows) > ry
      && field->fcol <= rx
      && (field->fcol + field->cols) > rx)
    {
      RETURN(E_OK);
    }
  RETURN(E_INVALID_FIELD);
}