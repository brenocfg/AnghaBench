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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  readadv (size_t) ; 
 void* readin (size_t) ; 

void bread (void *b, size_t len) {
  void *p = readin (len);
  assert (p != NULL);
  memcpy (b, p, len);
  readadv (len);
  //bytes_read += len;
}