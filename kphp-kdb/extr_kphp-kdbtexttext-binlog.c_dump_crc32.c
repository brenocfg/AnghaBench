#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lev_crc32 {int /*<<< orphan*/  crc32; int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 scalar_t__ dump_line_header (char*,char) ; 
 int /*<<< orphan*/  dumping_crc32 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out ; 

void dump_crc32 (struct lev_crc32 *E) {
  if (!dumping_crc32) { return; }
  if (dump_line_header ("LEV_CRC32", '\t')) {
    return;
  }
  fprintf (out, "%lld\t0x%x\n", E->pos, E->crc32);
}