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
struct pc_struct {int dummy; } ;
typedef  scalar_t__ pc_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

pc_t pc_new() {
  pc_t self = malloc(sizeof(struct pc_struct));
  if (self) {
    memset(self, 0, sizeof(struct pc_struct));
  }
  return self;
}