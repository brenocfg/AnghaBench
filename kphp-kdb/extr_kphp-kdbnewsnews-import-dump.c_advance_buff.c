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

/* Variables and functions */
 scalar_t__ IMPORT_BUFF_SIZE ; 
 scalar_t__ import_buff ; 
 int /*<<< orphan*/  import_fd ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ read (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ rend ; 
 scalar_t__ rptr ; 

void advance_buff (void) {
  //assert (rptr != import_buff);
  memmove (import_buff, rptr, rend - rptr);
  rend -= (rptr - import_buff);
  rptr = import_buff;
  rend += read (import_fd, rend, import_buff + IMPORT_BUFF_SIZE - rend);
}