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
struct buffered_logevent {void* data; } ;
typedef  int lev_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 

void *alloc_buffered_logevent (struct buffered_logevent *L, lev_type_t type, int size) {
  size = (size + 3) & -4;
  assert (size >= 4);
  L->data = calloc (size + 8, 1);
  assert (L->data != NULL);
  memcpy (L->data, &size, 4);
  memcpy (L->data + 8, &type, 4);
  return L->data + 8;
}