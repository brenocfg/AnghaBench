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
typedef  int /*<<< orphan*/  uv_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ pthread_key_delete (int /*<<< orphan*/ ) ; 

void uv_key_delete(uv_key_t* key) {
  if (pthread_key_delete(*key))
    abort();
}