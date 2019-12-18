#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  crc32_off; int /*<<< orphan*/  total_correct_crc32_logevents; } ;
typedef  TYPE_1__ file_t ;
struct TYPE_8__ {int /*<<< orphan*/  last_correct_off; } ;
typedef  TYPE_2__ crc32_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  file_crc32_correct_flush (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void file_crc32_correct_add (file_t *F, crc32_stat_t *S) {
  file_crc32_correct_flush (F, S);
  F->total_correct_crc32_logevents++;
  S->last_correct_off = F->crc32_off;
}