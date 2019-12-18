#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  query; int /*<<< orphan*/  expiration_time; int /*<<< orphan*/  res; int /*<<< orphan*/  cpu_time; } ;
typedef  TYPE_1__ search_query_heap_en_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void search_query_copy (search_query_heap_en_t *D, search_query_heap_en_t *S) {
  D->cpu_time = S->cpu_time;
  D->res = S->res;
  D->expiration_time = S->expiration_time;
  strcpy (D->query, S->query);
}