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
struct metafile_header_old {int /*<<< orphan*/  key_len; } ;
struct metafile_header {scalar_t__ crc32; int /*<<< orphan*/  key_len; } ;

/* Variables and functions */

void upgrade_header (struct metafile_header *x) {
  x->key_len = ((struct metafile_header_old *)x)->key_len;
  x->crc32 = 0;
}