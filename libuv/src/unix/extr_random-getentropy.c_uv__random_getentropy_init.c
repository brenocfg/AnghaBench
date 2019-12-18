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
typedef  scalar_t__ uv__getentropy_cb ;

/* Variables and functions */
 int /*<<< orphan*/  RTLD_DEFAULT ; 
 scalar_t__ dlsym (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ uv__getentropy ; 

__attribute__((used)) static void uv__random_getentropy_init(void) {
  uv__getentropy = (uv__getentropy_cb) dlsym(RTLD_DEFAULT, "getentropy");
}