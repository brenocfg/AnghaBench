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
struct transaction_buffer {long long size; scalar_t__ p; int /*<<< orphan*/  buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,long long) ; 
 int /*<<< orphan*/  malloc (long long) ; 

__attribute__((used)) static void tb_init (struct transaction_buffer *B, long long size) {
  B->buff = malloc (size);
  if (!B->buff) {
    kprintf ("Not enough memory to allocate transaction buffer (%lld bytes size).\n", size);
    exit (1);
  }
  B->size = size;
  B->p = 0;
}