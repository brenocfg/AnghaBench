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
struct partial_symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_NATURAL_NAME (struct partial_symbol* const) ; 
 int strcmp_iw_ordered (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_psymbols (const void *s1p, const void *s2p)
{
  struct partial_symbol *const *s1 = s1p;
  struct partial_symbol *const *s2 = s2p;

  return strcmp_iw_ordered (SYMBOL_NATURAL_NAME (*s1),
			    SYMBOL_NATURAL_NAME (*s2));
}