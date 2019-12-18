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
struct TYPE_2__ {int* tokens; } ;

/* Variables and functions */
#define  CAT 133 
#define  OR 132 
#define  ORTOP 131 
#define  PLUS 130 
#define  QMARK 129 
#define  STAR 128 
 TYPE_1__* dfa ; 

__attribute__((used)) static int
nsubtoks (int tindex)
{
  int ntoks1;

  switch (dfa->tokens[tindex - 1])
    {
    default:
      return 1;
    case QMARK:
    case STAR:
    case PLUS:
      return 1 + nsubtoks(tindex - 1);
    case CAT:
    case OR:
    case ORTOP:
      ntoks1 = nsubtoks(tindex - 1);
      return 1 + ntoks1 + nsubtoks(tindex - 1 - ntoks1);
    }
}