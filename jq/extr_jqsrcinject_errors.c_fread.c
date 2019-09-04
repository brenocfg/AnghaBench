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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  GET_REAL (size_t (*) (void*,size_t,size_t,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/ * fail_read ; 
 size_t real_fread (void*,size_t,size_t,int /*<<< orphan*/ *) ; 

size_t fread(void *buf, size_t sz, size_t nemb, FILE *f) {
  GET_REAL(fread);
  size_t res = real_fread(buf, sz, nemb, f);
  if (fail_read == f)
    return 0;
  return res;
}