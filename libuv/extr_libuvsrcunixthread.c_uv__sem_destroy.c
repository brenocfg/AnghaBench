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
typedef  int /*<<< orphan*/  uv_sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ sem_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uv__sem_destroy(uv_sem_t* sem) {
  if (sem_destroy(sem))
    abort();
}