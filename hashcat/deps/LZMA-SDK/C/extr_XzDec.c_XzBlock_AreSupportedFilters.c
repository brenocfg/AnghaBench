#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* filters; } ;
struct TYPE_5__ {scalar_t__ id; int propsSize; int* props; } ;
typedef  TYPE_1__ CXzFilter ;
typedef  TYPE_2__ CXzBlock ;
typedef  int /*<<< orphan*/  BoolInt ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ XZ_ID_Delta ; 
 scalar_t__ XZ_ID_LZMA2 ; 
 scalar_t__ XZ_ID_SPARC ; 
 int XzBlock_GetNumFilters (TYPE_2__ const*) ; 

__attribute__((used)) static BoolInt XzBlock_AreSupportedFilters(const CXzBlock *p)
{
  unsigned numFilters = XzBlock_GetNumFilters(p) - 1;
  unsigned i;
  {
    const CXzFilter *f = &p->filters[numFilters];
    if (f->id != XZ_ID_LZMA2 || f->propsSize != 1 || f->props[0] > 40)
      return False;
  }

  for (i = 0; i < numFilters; i++)
  {
    const CXzFilter *f = &p->filters[i];
    if (f->id == XZ_ID_Delta)
    {
      if (f->propsSize != 1)
        return False;
    }
    else if (f->id < XZ_ID_Delta
        || f->id > XZ_ID_SPARC
        || (f->propsSize != 0 && f->propsSize != 4))
      return False;
  }
  return True;
}