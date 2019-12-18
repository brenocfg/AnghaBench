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
struct tl_hashmap {int size; int /*<<< orphan*/  h; } ;

/* Variables and functions */
 int /*<<< orphan*/  tl_zzfree (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfree (struct tl_hashmap*,int) ; 

void tl_hashmap_free (struct tl_hashmap **V) {
  struct tl_hashmap *H = *V;
  if (H == NULL) {
    return;
  }
  tl_zzfree (H->h, (H->size * sizeof (void *)));
  zfree (H, sizeof (struct tl_hashmap));
  *V = NULL;
}