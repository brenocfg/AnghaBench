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
typedef  int /*<<< orphan*/  ptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dfaerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (size_t) ; 

__attribute__((used)) static ptr_t
xmalloc (size_t n)
{
  ptr_t r = malloc(n);

  assert(n != 0);
  if (!r)
    dfaerror(_("Memory exhausted"));
  return r;
}