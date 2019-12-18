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
struct TYPE_3__ {char* desc; char* age; char* sum; char* avg; char* max_val; char* max_desc; } ;
typedef  TYPE_1__ stat_text_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void print_stat_callback (stat_text_t *s) {
  fprintf (stderr, "%s %s [sum = %s] [avg = %s] [max = %s|%s]\n", s->desc, s->age, s->sum, s->avg, s->max_val, s->max_desc);
}