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
struct iwdpm_struct {int dummy; } ;
typedef  int /*<<< orphan*/ * iwdpm_t ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

iwdpm_t iwdpm_new(int argc, char **argv, int *to_exit) {
  iwdpm_t self = malloc(sizeof(struct iwdpm_struct));
  if (!self) {
    return NULL;
  }
  memset(self, 0, sizeof(struct iwdpm_struct));
  return self;
}