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
typedef  int /*<<< orphan*/  listree_t ;

/* Variables and functions */
 char* metafile_get_text (int,int*) ; 
 int /*<<< orphan*/  writeout (char*,int) ; 

__attribute__((used)) static int array_write_text (listree_t *LT, int temp_id) {
  int text_len;
  char *p = metafile_get_text (temp_id, &text_len);
  writeout (p, text_len);
  return 0;
}