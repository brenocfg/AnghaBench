#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct locfile {int dummy; } ;
struct TYPE_8__ {scalar_t__ start; scalar_t__ end; } ;
typedef  TYPE_1__ location ;
struct TYPE_9__ {int /*<<< orphan*/  locfile; TYPE_1__ source; struct TYPE_9__* next; } ;
typedef  TYPE_2__ inst ;
struct TYPE_10__ {TYPE_2__* first; } ;
typedef  TYPE_3__ block ;
struct TYPE_11__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 TYPE_7__ UNKNOWN_LOCATION ; 
 int /*<<< orphan*/  locfile_retain (struct locfile*) ; 

block gen_location(location loc, struct locfile* l, block b) {
  for (inst* i = b.first; i; i = i->next) {
    if (i->source.start == UNKNOWN_LOCATION.start &&
        i->source.end == UNKNOWN_LOCATION.end) {
      i->source = loc;
      i->locfile = locfile_retain(l);
    }
  }
  return b;
}