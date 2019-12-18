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
typedef  int /*<<< orphan*/  jvp_literal_number ;
typedef  int /*<<< orphan*/  decNumberUnit ;

/* Variables and functions */
 unsigned int DECDPUN ; 
 int /*<<< orphan*/ * jv_mem_alloc (int) ; 

__attribute__((used)) static jvp_literal_number* jvp_literal_number_alloc(unsigned literal_length) {

  /* The number of units needed is ceil(DECNUMDIGITS/DECDPUN)         */
  int units = ((literal_length+DECDPUN-1)/DECDPUN);

  jvp_literal_number* n = jv_mem_alloc(
    sizeof(jvp_literal_number)
    + sizeof(decNumberUnit) * units
  );

  return n;
}