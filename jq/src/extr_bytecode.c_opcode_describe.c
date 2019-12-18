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
struct opcode_description {int dummy; } ;
typedef  size_t opcode ;

/* Variables and functions */
 int NUM_OPCODES ; 
 struct opcode_description const invalid_opcode_description ; 
 struct opcode_description const* opcode_descriptions ; 

const struct opcode_description* opcode_describe(opcode op) {
  if ((int)op >= 0 && (int)op < NUM_OPCODES) {
    return &opcode_descriptions[op];
  } else {
    return &invalid_opcode_description;
  }
}