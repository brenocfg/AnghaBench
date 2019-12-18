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
struct TYPE_2__ {scalar_t__ files; } ;
typedef  TYPE_1__ cache_stat_server_t ;

/* Variables and functions */
 int cmp_stat_server_id (void const*,void const*) ; 

__attribute__((used)) static int cmp_stat_server_files (const void *x, const void *y) {
  cache_stat_server_t *a = *(cache_stat_server_t **) x;
  cache_stat_server_t *b = *(cache_stat_server_t **) y;
  if (a->files > b->files) {
    return -1;
  }
  if (a->files < b->files) {
    return 1;
  }
  return cmp_stat_server_id (x, y);
}