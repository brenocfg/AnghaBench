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
struct netbuffer {int dummy; } ;
struct nb_reader {int bytes; int /*<<< orphan*/  it; scalar_t__ ptr_s; scalar_t__ ptr_e; scalar_t__ p; scalar_t__ bytes_read; } ;

/* Variables and functions */
 scalar_t__ nbit_get_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ nbit_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,struct netbuffer*) ; 

void nb_reader_set (struct nb_reader *I, struct netbuffer *In, const int bytes) {
  I->bytes = bytes;
  I->bytes_read = 0;
  nbit_set (&I->it, In);
  I->p = I->ptr_s = nbit_get_ptr (&I->it);
  I->ptr_e = I->ptr_s + nbit_ready_bytes (&I->it);
}