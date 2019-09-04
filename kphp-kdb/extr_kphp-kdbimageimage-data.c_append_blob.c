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
struct forth_output {int l; scalar_t__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 

__attribute__((used)) static int append_blob (struct forth_output *O, void *blob, size_t size) {
  if (O == NULL) { return -1; }
  int o = (sizeof (O->s) - O->l);
  if (o < size) {
    return -1;
  }
  memcpy (O->s + O->l, blob, size);
  O->l += size;
  return 0;
}