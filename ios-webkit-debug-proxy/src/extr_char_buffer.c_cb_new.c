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
struct cb_struct {int dummy; } ;
typedef  scalar_t__ cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

cb_t cb_new() {
  cb_t self = (cb_t)malloc(sizeof(struct cb_struct));
  if (self) {
    memset(self, 0, sizeof(struct cb_struct));
  }
  return self;
}