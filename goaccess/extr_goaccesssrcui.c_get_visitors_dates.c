#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int holder_size; int idx; TYPE_2__* items; } ;
struct TYPE_6__ {TYPE_1__* metrics; } ;
struct TYPE_5__ {char* data; } ;
typedef  TYPE_3__ GHolder ;

/* Variables and functions */
 char** malloc (int) ; 
 int /*<<< orphan*/  qsort (char**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp_asc ; 

__attribute__((used)) static char **
get_visitors_dates (GHolder * h)
{
  char **dates = malloc (sizeof (char *) * h->holder_size);
  int i;

  for (i = 0; i < h->idx; i++) {
    dates[i] = h->items[i].metrics->data;
  }
  qsort (dates, h->holder_size, sizeof (char *), strcmp_asc);

  return dates;
}