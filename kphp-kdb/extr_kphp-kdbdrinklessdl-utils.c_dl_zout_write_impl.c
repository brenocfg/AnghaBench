#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t id; int written; int /*<<< orphan*/  crc32_complement; scalar_t__ use_crc32; } ;
typedef  TYPE_1__ dl_zout ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  crc32_partial (void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fd ; 
 int* fpos ; 
 int write (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int dl_zout_write_impl (dl_zout *f, const void *src, int len) {
  assert (write (fd[f->id], src, (size_t)len) == len);
  fpos[f->id] += len;

  if (f->use_crc32) {
    f->crc32_complement = crc32_partial (src, len, f->crc32_complement);
  }
  f->written += len;
  return len;
}